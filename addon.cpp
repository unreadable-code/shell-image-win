#include "file_image.h"

NAN_METHOD(getImageForPath) {
    if (info.Length() < 5) {
        Nan::ThrowTypeError("Invalid number of arguments: expected 5 arguments");
        return;
    }

    if (!info[0]->IsString()) {
        Nan::ThrowTypeError("Invalid argument 'path': expected String");
        return;
    }

    if (!info[1]->IsNumber()) {
        Nan::ThrowTypeError("Invalid argument 'width': expected Number");
        return;
    }

    if (!info[2]->IsNumber()) {
        Nan::ThrowTypeError("Invalid argument 'height': expected Number");
        return;
    }

    if (!info[3]->IsNumber()) {
        Nan::ThrowTypeError("Invalid argument 'flags': expected Number");
        return;
    }

    if (!info[4]->IsFunction()) {
        Nan::ThrowTypeError("Invalid argument 'callback': expected Function");
        return;
    }

    v8::Isolate* isolate = info.GetIsolate();
    v8::Local<v8::Context> context = Nan::GetCurrentContext();
    v8::Local<v8::String> path = info[0]->ToString(context).ToLocalChecked();
    v8::String::Utf8Value pathValue(isolate, path);
    int32_t width = info[1]->Int32Value(context).ToChecked();
    int32_t height = info[2]->Int32Value(context).ToChecked();
    int32_t flags = info[3]->Int32Value(context).ToChecked();
    auto callback = new Nan::Callback(info[4].As<v8::Function>());

    Nan::AsyncQueueWorker(new FileImageAsyncWorker(*pathValue, width, height, flags, callback));
}

NAN_MODULE_INIT(init) {
    NAN_EXPORT(target, getImageForPath);

    Nan::Set(
        target,
        Nan::New("ResizeToFit").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_RESIZETOFIT))
    );

    Nan::Set(
        target,
        Nan::New("BiggerSizeOk").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_BIGGERSIZEOK))
    );

    Nan::Set(
        target,
        Nan::New("MemoryOnly").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_MEMORYONLY))
    );

    Nan::Set(
        target,
        Nan::New("IconOnly").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_ICONONLY))
    );

    Nan::Set(
        target,
        Nan::New("ThumbnailOnly").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_THUMBNAILONLY))
    );

    Nan::Set(
        target,
        Nan::New("InCacheOnly").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_INCACHEONLY))
    );

    Nan::Set(
        target,
        Nan::New("CropToSquare").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_CROPTOSQUARE))
    );

    Nan::Set(
        target,
        Nan::New("WideThumbnails").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_WIDETHUMBNAILS))
    );

    Nan::Set(
        target,
        Nan::New("IconBackground").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_ICONBACKGROUND))
    );

    Nan::Set(
        target,
        Nan::New("ScaleUp").ToLocalChecked(),
        Nan::New(static_cast<uint32_t>(SIIGBF_SCALEUP))
    );
}

NODE_MODULE(file_image, init);
