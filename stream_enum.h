// stream_enum.h
#ifndef STREAM_ENUM_H
#define STREAM_ENUM_H

struct Streams {
    enum StreamType {
        hls_stream,
        secure_hls_stream,
        shoutcast_stream,
        secure_shoutcast_stream
    };
};

enum Hits {
    id,
    score,
    name,
    responseType,
    description,
    band,
    callLetters,
    logo,
    freq,
    cume,
    countries,
    isActive,
    modified,
    market,
    HitsCount,
    streamType // This could be used to refer to Streams::StreamType
};

#endif // STREAM_ENUM_H
