#ifndef __BINARYIO_H__
#define __BINARYIO_H__

#include <string>
#include <utility>

class BinaryIO {
   public:
    /* Writes to a binary file named ++filename++.
     * ++serial_tree++ should be a serialized Huffman tree, and
     * ++bitstring++ should be a string of 0s and 1s
     * comprising the encoded text.
     *
     * Possible exception: Will throw a runtime_error if given
     * ++bitstring++ is larger than 2^32 bits.
     */
    void writeFile(const std::string &filename, const std::string &serial_tree,
                   const std::string &bitstring);

    /* Reads from zapped file named ++filename++.
     * returns a pair. A pair is a special C++ 
     * data structure that holds 2 elements. The
     * first element contains the serialized Huffman tree, and
     * the second element contains the encoded text.
     */
    std::pair<std::string, std::string> readFile(const std::string &filename);

   private:
    template <typename streamtype>
    void open_or_die(streamtype &stream, const std::string &filename);
};

#endif
