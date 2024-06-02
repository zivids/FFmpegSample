package com.coocent.ffmpegsample

import android.os.Bundle
import android.view.SurfaceHolder
import android.view.View
import android.view.View.OnClickListener
import androidx.appcompat.app.AppCompatActivity
import com.coocent.ffmpeg.FFmpegPlayer
import com.coocent.ffmpeg.listener.OnPreparedListener
import com.coocent.ffmpegsample.databinding.ActivityFfmpegBinding

/**
 * @author coocent-camera002
 * @date Created on 2024/5/7.
 */
class FFmpegActivity : AppCompatActivity(), OnClickListener
{
    private lateinit var binding: ActivityFfmpegBinding
    private lateinit var ffmpegPlayer: FFmpegPlayer

    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        binding = ActivityFfmpegBinding.inflate(layoutInflater)
        setContentView(binding.root)

        ffmpegPlayer = FFmpegPlayer()
        ffmpegPlayer.setDataSource("/sdcard/Download/任意门.MP4")
        ffmpegPlayer.setOnPreparedListener(object : OnPreparedListener
        {
            override fun onPrepared()
            {
                binding.playButton.isEnabled = true
                binding.pauseButton.isEnabled = true
            }
        })
        binding.surfaceView.holder.addCallback(object : SurfaceHolder.Callback
        {
            override fun surfaceCreated(holder: SurfaceHolder)
            {
                ffmpegPlayer.setSurface(holder.surface)
                ffmpegPlayer.prepareAsync()
            }

            override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int)
            {

            }

            override fun surfaceDestroyed(holder: SurfaceHolder)
            {

            }
        })

        binding.playButton.setOnClickListener(this)
        binding.pauseButton.setOnClickListener(this)
    }

    override fun onClick(v: View)
    {
        when (v.id)
        {
            R.id.play_button ->
            {
                ffmpegPlayer.start()
            }
            R.id.pause_button ->
            {
                ffmpegPlayer.pause()
            }
        }
    }

    override fun onDestroy()
    {
        super.onDestroy()
        ffmpegPlayer.release()
    }
}