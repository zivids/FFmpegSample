package com.coocent.ffmpeg

import com.coocent.ffmpeg.listener.OnPreparedListener

/**
 * @author coocent-camera002
 * @date Created on 2024/4/29.
 */
class FFmpegPlayer : OnPreparedListener
{
    companion object
    {
        init
        {
            System.loadLibrary("ffmpeg-sample-player")
        }

        fun getFFmpegVersion() = nativeGetFFmpegVersion()

        private external fun nativeGetFFmpegVersion(): String
    }

    private var playerHandle: Long = -1L
    private var onPreparedListener: OnPreparedListener? = null

    init
    {
        playerHandle = nativeCreatePlayer()
        if (playerHandle == -1L)
        {
            throw IllegalStateException("Can not create player")
        }
    }

    override fun onPrepared()
    {
        onPreparedListener?.onPrepared()
    }

    fun setDataSource(path: String)
    {
        nativeSetDataSource(playerHandle, path)
    }

    fun prepareAsync()
    {
        nativePrepareAsync(playerHandle)
    }

    fun start()
    {
        nativeStart(playerHandle)
    }

    fun release()
    {
        nativeRelease(playerHandle)
        playerHandle = -1L
    }

    fun setOnPreparedListener(listener: OnPreparedListener)
    {
        onPreparedListener = listener
    }

    private external fun nativeCreatePlayer(): Long

    private external fun nativeSetDataSource(handle: Long, path: String)

    private external fun nativePrepareAsync(handle: Long)

    private external fun nativeStart(handle: Long)

    private external fun nativePause(handle: Long)

    private external fun nativeStop(handle: Long)

    private external fun nativeSeekTo(handle: Long, position: Long)

    private external fun nativeRelease(handle: Long)
}