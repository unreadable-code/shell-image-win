#include <nan.h>
#include <string>
#include <windows.h>
#include <shobjidl.h>
#include <cstddef>
#include <cwchar>
#include <memory>
#include <algorithm>

class FileImageAsyncWorker : public Nan::AsyncWorker {
    public:
        FileImageAsyncWorker(const char* name, int32_t width, int32_t height, int32_t flags, Nan::Callback* callback)
            : Nan::AsyncWorker(callback), _name(name), _width(width), _height(height), _flags(flags)
        {
            // Empty constructor
        }

        void Execute() override;

    protected:
        void HandleOKCallback() override {
            if (!_result.empty()) {
                v8::Local<v8::Value> argv[] = {
                    Nan::Null(),
                    Nan::CopyBuffer(
                        static_cast<char*>(static_cast<void*>(_result.data())),
                        _result.size()
                    ).ToLocalChecked(),
                };

                callback->Call(2, argv);
            } else {
                v8::Local<v8::Value> argv[] = { Nan::Error("Failed to load image") };
                callback->Call(1, argv);
            }
        }

    private:
        std::string const _name;
        int32_t const _width;
        int32_t const _height;
        int32_t const _flags;
        std::vector<unsigned char> _result;
};
