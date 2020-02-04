export enum flags {
    ResizeToFit,
    BiggerSizeOk,
    MemoryOnly,
    IconOnly,
    ThumbnailOnly,
    InCacheOnly,
    CropToSquare,
    WideThumbnails,
    IconBackground,
    ScaleUp,
}

export interface Options {
    width: number;
    height: number;
    flags: flags;
}

export function getImageForPath(path: string, options: Options): Promise<Buffer>;
