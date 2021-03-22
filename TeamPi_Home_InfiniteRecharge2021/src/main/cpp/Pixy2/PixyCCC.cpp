#include "Pixy2/Pixy2CCC.h"


Pixy2CCC::Pixy2CCC(Pixy2 *pixy)
{
    this->pixy = pixy;
}

Pixy2CCC::~Pixy2CCC()
{
}

/**
 * <p>Gets ArrayList of signature blocks from cache</p>
 * 
 * <p>{@link #getBlocks(boolean, int, int)} must be executed first to get the data actual from Pixy2</p>
 * 
 * @return Pixy2 signature Blocks
 */
std::vector<Block> *Pixy2CCC::getBlockCache() {
    return blocks;
}

/**
 * <p>Gets signature {@link Block}s from Pixy2</p>
 * 
 * <p>Defaults to waiting for a response, getting blocks from all signatures and a maximum of all 256 blocks</p>
 * 
 * <p>Returned data should be retrieved from the cache with {@link #getBlockCache()}</p>
 * 
 * @return Pixy2 error code
 */
int Pixy2CCC::getBlocks() {
    return getBlocks(true, CCC_SIG_ALL, 0xff);
}

/**
 * <p>Gets signature {@link Block}s from Pixy2</p>
 * 
 * <p>Defaults to getting blocks from all signatures and a maximum of all 256 blocks</p>
 * 
 * <p>Returned data should be retrieved from the cache with {@link #getBlockCache()}</p>
 * 
 * @param wait      Whether to wait for Pixy2 if data is not available
 * 
 * @return Pixy2 error code
 */
int Pixy2CCC::getBlocks(bool wait) {
    return getBlocks(wait, CCC_SIG_ALL, 0xff);
}

/**
 * <p>Gets signature {@link Block}s from Pixy2</p>
 * 
 * <p>Defaults to getting a maximum of all 256 blocks</p>
 * 
 * <p>Returned data should be retrieved from the cache with {@link #getBlockCache()}</p>
 * 
 * @param wait      Whether to wait for Pixy2 if data is not available
 * @param sigmap    Sigmap to look for
 * 
 * @return Pixy2 error code
 */
int Pixy2CCC::getBlocks(bool wait, int sigmap) {
    return getBlocks(wait, sigmap, 0xff);
}

/**
 * <p>Gets signature {@link Block}s from Pixy2</p>
 * 
 * <p>Returned data should be retrieved from the cache with {@link #getBlockCache()}</p>
 * 
 * @param wait      Whether to wait for Pixy2 if data is not available
 * @param sigmap    Sigmap to look for
 * @param maxBlocks Maximum blocks to look for
 * 
 * @return Pixy2 error code
 */
int Pixy2CCC::getBlocks(bool wait, int sigmap, int maxBlocks) {
    long start = (long)frc::GetTime();

    numBlocks = 0;

    while (true) {
        // Fill in request data
        pixy->bufferPayload[0] = sigmap;
        pixy->bufferPayload[1] = maxBlocks;
        pixy->length = 2;
        pixy->type = CCC_REQUEST_BLOCKS;

        // Send request
        pixy->sendPacket();
        if (pixy->receivePacket() == 0) {
            if (pixy->type == CCC_RESPONSE_BLOCKS) {
                // Clears current cache of blocks
                blocks->clear();
                // Iterates through and creates block objects from buffer
                for (int i = 0; i + 13 < pixy->length; i += 14) {
                    Block *b = new Block(((pixy->buffer[i + 1] & 0xff) << 8) | (pixy->buffer[i] & 0xff),
                            ((pixy->buffer[i + 3] & 0xff) << 8) | (pixy->buffer[i + 2] & 0xff),
                            ((pixy->buffer[i + 5] & 0xff) << 8) | (pixy->buffer[i + 4] & 0xff),
                            ((pixy->buffer[i + 7] & 0xff) << 8) | (pixy->buffer[i + 6] & 0xff),
                            ((pixy->buffer[i + 9] & 0xff) << 8) | (pixy->buffer[i + 8] & 0xff),
                            ((pixy->buffer[i + 11] & 0xff) << 8) | (pixy->buffer[i + 10] & 0xff),
                            (pixy->buffer[i + 12] & 0xff), (pixy->buffer[i + 13] & 0xff));
                    blocks->push_back(*b);
                }
                numBlocks = blocks->size(); // Success
                return numBlocks;
            } else if (pixy->type == PIXY_TYPE_RESPONSE_ERROR) {
                // Deal with busy and program changing states from Pixy2 (we'll wait)
                if (pixy->buffer[0] == PIXY_RESULT_BUSY) {
                    if (!wait)
                        return PIXY_RESULT_BUSY; // New data not available yet
                } else if (pixy->buffer[0] == PIXY_RESULT_PROG_CHANGING) {
                    return pixy->buffer[0];
                }

            }
        } else {
            return PIXY_RESULT_ERROR; // Some kind of bitstream error
        }
        if (frc::GetTime() - start > 500) {
            return PIXY_RESULT_ERROR; // Timeout to prevent lockup
        }
        // If we're waiting for frame data, don't thrash Pixy with requests.
        // We can give up half a millisecond of latency (worst case)
        frc::Wait(0.5);
    }
}
