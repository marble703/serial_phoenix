#include <cstdint>
template<>
inline SerialCode Serial::read_unsafe(std::vector<uint8_t>& out) {
    if (!this->is_open()) {
        return SerialCode::Value::READ_NOT_OPENED;
    }
    try {
        this->read_buffer_.resize(out.size());
        // 从串口读取到本地缓冲区
        this->serial_port_->receive(this->read_buffer_);
    } catch (const std::exception& e) {
        return SerialCode::Value::READ_FAIL;
    }
    std::memcpy(out.data(), this->read_buffer_.data(), out.size());
    return SerialCode::Value::OK;
}

template<>
inline SerialCode Serial::read(std::vector<uint8_t>& out) {
    std::lock_guard<std::mutex> read_guard(this->read_mutex_);

    if (!this->is_open()) {
        return SerialCode::Value::READ_NOT_OPENED;
    }

    std::vector<uint8_t> read_buffer;

    try {
        read_buffer.resize(out.size());
        this->serial_port_->receive(read_buffer);

    } catch (const std::exception& e) {
        return SerialCode::Value::READ_FAIL;
    }
    std::memcpy(out.data(), read_buffer.data(), out.size());
    return SerialCode::Value::OK;
}

template<typename T>
inline SerialCode Serial::read_unsafe(T& out) {
    static_assert(std::is_trivially_copyable_v<T>, "out type must be TriviallyCopyable for memcpy");

    if (!this->is_open()) {
        return SerialCode::Value::READ_NOT_OPENED;
    }
    try {
        this->read_buffer_.resize(sizeof(T));
        this->serial_port_->receive(this->read_buffer_);
    } catch (const std::exception& e) {
        return SerialCode::Value::READ_FAIL;
    }

    std::memcpy(&out, this->read_buffer_.data(), sizeof(T));
    return SerialCode::Value::OK;
}

template<typename T>
inline SerialCode Serial::read(T& out) {
    static_assert(std::is_trivially_copyable_v<T>, "out type must be TriviallyCopyable for memcpy");

    std::lock_guard<std::mutex> read_guard(this->read_mutex_);

    if (!this->is_open()) {
        return SerialCode::Value::READ_NOT_OPENED;
    }

    std::vector<uint8_t> read_buffer;

    try {
        read_buffer.resize(sizeof(T));
        this->serial_port_->receive(read_buffer);
    } catch (const std::exception& e) {
        return SerialCode::Value::READ_FAIL;
    }

    std::memcpy(&out, read_buffer.data(), sizeof(T));
    return SerialCode::Value::OK;
}

template<>
inline SerialCode Serial::write_unsafe(std::vector<uint8_t>& in) {
    if (!this->is_open()) {
        return SerialCode::Value::WRITE_NOT_OPENED;
    }
    try {
        this->write_buffer_.resize(in.size());
        std::memcpy(this->write_buffer_.data(), in.data(), in.size());
        this->serial_port_->send(this->write_buffer_);
    } catch (const std::exception& e) {
        return SerialCode::Value::WRITE_FAIL;
    }
    return SerialCode::Value::OK;
}

template<>
inline SerialCode Serial::write(std::vector<uint8_t>& in) {
    std::lock_guard<std::mutex> write_guard(this->write_mutex_);

    if (!this->is_open()) {
        return SerialCode::Value::WRITE_NOT_OPENED;
    }

    std::vector<uint8_t> write_buffer;

    try {
        write_buffer.resize(in.size());
        std::memcpy(write_buffer.data(), in.data(), in.size());
        this->serial_port_->send(write_buffer);
    } catch (const std::exception& e) {
        return SerialCode::Value::WRITE_FAIL;
    }
    return SerialCode::Value::OK;
}

template<typename T>
inline SerialCode Serial::write_unsafe(T&& in) {
    static_assert(std::is_trivially_copyable_v<T>, "T must be TriviallyCopyable for wire send");

    if (!this->is_open()) {
        return SerialCode::Value::WRITE_NOT_OPENED;
    }
    try {
        this->write_buffer_.resize(sizeof(T));
        std::memcpy(this->write_buffer_.data(), &in, sizeof(T));
        this->serial_port_->send(this->write_buffer_);
    } catch (const std::exception& e) {
        return SerialCode::Value::WRITE_FAIL;
    }
    return SerialCode::Value::OK;
}

template<typename T>
inline SerialCode Serial::write(T&& in) {
    static_assert(std::is_trivially_copyable_v<T>, "T must be TriviallyCopyable for wire send");

    std::lock_guard<std::mutex> write_guard(this->write_mutex_);

    if (!this->is_open()) {
        return SerialCode::Value::WRITE_NOT_OPENED;
    }

    std::vector<uint8_t> write_buffer;

    try {
        write_buffer.resize(sizeof(T));
        std::memcpy(write_buffer.data(), &in, sizeof(T));
        this->serial_port_->send(write_buffer);
    } catch (const std::exception& e) {
        return SerialCode::Value::WRITE_FAIL;
    }
    return SerialCode::Value::OK;
}
