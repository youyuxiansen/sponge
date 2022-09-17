#include "byte_stream.hh"

#include <list>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) : _capacity(capacity) {}

size_t ByteStream::write(const string &data) {
    size_t write_count = 0;
    for (const char c : data) {
        if (_capacity - _buff_size <= 0)
            break;
        else {
            if (!_end_input) {
                _buff.push_back(c);
                write_count++;
                _nwrite++;
                _buff_size++;
            }
        }
    }
    return write_count;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    const size_t peek_length = len > _buff_size ? _buff_size : len;
    list<char>::const_iterator it = _buff.begin();
    advance(it, peek_length);
    return string(_buff.begin(), it);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t pop_length = len > _buff_size ? _buff_size : len;
    _nread += pop_length;
    _buff_size -= pop_length;
    while (pop_length--)
        _buff.pop_front();
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    const string s = peek_output(len);
    pop_output(len);
    return s;
}

void ByteStream::end_input() { _end_input = true; }

bool ByteStream::input_ended() const { return _end_input; }

size_t ByteStream::buffer_size() const { return _buff_size; }

bool ByteStream::buffer_empty() const { return _buff_size == 0; }

bool ByteStream::eof() const { return _end_input && buffer_empty(); }

size_t ByteStream::bytes_written() const { return _nwrite; }

size_t ByteStream::bytes_read() const { return _nread; }

size_t ByteStream::remaining_capacity() const { return _capacity - _buff_size; }
