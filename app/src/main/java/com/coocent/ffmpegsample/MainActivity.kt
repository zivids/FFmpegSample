package com.coocent.ffmpegsample

import android.media.MediaPlayer
import android.media.MediaPlayer.OnPreparedListener
import android.os.Bundle
import android.util.Log
import android.view.View
import android.view.View.OnClickListener
import androidx.appcompat.app.AppCompatActivity
import com.coocent.ffmpeg.FFmpegPlayer
import com.coocent.ffmpegsample.databinding.ActivityMainBinding

/**
 * @author coocent-camera002
 * @date Created on 2024/4/29.
 */
class MainActivity : AppCompatActivity(), OnClickListener
{
    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        Log.d("TAGF", FFmpegPlayer.getFFmpegVersion())
        val player = FFmpegPlayer()
        player.setDataSource("test ffmpeg")
        player.prepareAsync()

        binding.ffmpegButton.setOnClickListener(this)
        binding.mediaButton.setOnClickListener(this)
    }

    override fun onClick(v: View)
    {
        when (v.id)
        {
            R.id.ffmpeg_button -> {}
            R.id.media_button -> {}
        }
    }
}