#ifndef __HELPER_H__
#define __HELPER_H__
#include "world_ups.pb.h"
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <math.h>
template <typename K, typename P> P getDist(K x1, K y1, K x2, K y2) {
  K diff_x = (x1 - x2);
  K diff_y = (y1 - y2);
  P res = pow(diff_x, 2) + pow(diff_y, 2);
  res = sqrt(res);
  return res;
}

// this is adpated from code that a Google engineer posted online
template <typename T>
bool sendMesgTo(const T &message, google::protobuf::io::FileOutputStream *out) {
  { // extra scope: make output go away before out->Flush()
    // We create a new coded stream for each message.
    // Don’t worry, this is fast.
    google::protobuf::io::CodedOutputStream output(out);
    // Write the size.
    const int size = message.ByteSize();
    output.WriteVarint32(size);
    uint8_t *buffer = output.GetDirectBufferForNBytesAndAdvance(size);
    if (buffer != NULL) {
      // Optimization: The message fits in one buffer, so use the faster
      // direct-to-array serialization path.
      message.SerializeWithCachedSizesToArray(buffer);
    } else {
      // Slightly-slower path when the message is multiple buffers.
      message.SerializeWithCachedSizes(&output);
      if (output.HadError()) {
        return false;
      }
    }
  }
  out->Flush();
  return true;
}

// this is adpated from code that a Google engineer posted online
template <typename T>
bool recvMesgFrom(T &message, google::protobuf::io::FileInputStream *in) {
  google::protobuf::io::CodedInputStream input(in);
  uint32_t size;
  if (!input.ReadVarint32(&size)) {
    return false;
  }
  // Tell the stream not to read beyond that size.
  google::protobuf::io::CodedInputStream::Limit limit = input.PushLimit(size);
  // Parse the message.
  if (!message.MergeFromCodedStream(&input)) {
    return false;
  }
  if (!input.ConsumedEntireMessage()) {
    return false;
  }
  // Release the limit.
  input.PopLimit(limit);
  return true;
}
#endif

/*
 * msgToCharArray
 *
 * convert google protocol message to vector char
 *
 * if success return 0, else -1
 * when message is not fully initialized, it fail.
 */
/*template <typename T> int msgToCharArray(T &message, std::vector<char> &buf) {
  bool isInitialized = message.IsInitialized();
  if (!isInitialized)
    return -1;
  size_t size = message.ByteSize();
  buf.resize(size);
  message.SerializeToArray(&buf[0], size);
  std::string tmp = std::to_string(size);
  tmp.push_back('\n');
  buf.insert(buf.begin(), tmp.begin(), tmp.end());
  return 0;
}
*/
