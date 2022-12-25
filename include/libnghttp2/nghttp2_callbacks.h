#pragma once

#if defined _WIN32 || defined _WIN64
#define NGHTTP2_IMPORT __declspec(dllimport)
#elif defined __linux__
#define NGHTTP2_IMPORT __attribute__ ((visibility ("default")))
#endif

NGHTTP2_IMPORT int nghttp2_session_callbacks_new(nghttp2_session_callbacks** callbacks_ptr);

NGHTTP2_IMPORT void nghttp2_session_callbacks_del(nghttp2_session_callbacks* callbacks);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_send_callback(nghttp2_session_callbacks* cbs, nghttp2_send_callback send_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_recv_callback(
    nghttp2_session_callbacks* cbs, nghttp2_recv_callback recv_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_on_frame_recv_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_on_frame_recv_callback on_frame_recv_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_on_invalid_frame_recv_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_on_invalid_frame_recv_callback on_invalid_frame_recv_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_on_data_chunk_recv_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_on_data_chunk_recv_callback on_data_chunk_recv_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_before_frame_send_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_before_frame_send_callback before_frame_send_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_on_frame_send_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_on_frame_send_callback on_frame_send_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_on_frame_not_send_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_on_frame_not_send_callback on_frame_not_send_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_on_stream_close_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_on_stream_close_callback on_stream_close_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_on_begin_headers_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_on_begin_headers_callback on_begin_headers_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_on_header_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_on_header_callback on_header_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_on_header_callback2(
    nghttp2_session_callbacks* cbs,
    nghttp2_on_header_callback2 on_header_callback2);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_on_invalid_header_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_on_invalid_header_callback on_invalid_header_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_on_invalid_header_callback2(
    nghttp2_session_callbacks* cbs,
    nghttp2_on_invalid_header_callback2 on_invalid_header_callback2);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_select_padding_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_select_padding_callback select_padding_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_data_source_read_length_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_data_source_read_length_callback data_source_read_length_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_on_begin_frame_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_on_begin_frame_callback on_begin_frame_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_send_data_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_send_data_callback send_data_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_pack_extension_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_pack_extension_callback pack_extension_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_unpack_extension_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_unpack_extension_callback unpack_extension_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_on_extension_chunk_recv_callback(
    nghttp2_session_callbacks* cbs,
    nghttp2_on_extension_chunk_recv_callback on_extension_chunk_recv_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_error_callback(
    nghttp2_session_callbacks* cbs, nghttp2_error_callback error_callback);

NGHTTP2_IMPORT void nghttp2_session_callbacks_set_error_callback2(
    nghttp2_session_callbacks* cbs, nghttp2_error_callback2 error_callback2);