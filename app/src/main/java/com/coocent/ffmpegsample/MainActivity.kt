package com.coocent.ffmpegsample

import android.Manifest
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Build
import android.os.Bundle
import android.view.View
import android.view.View.OnClickListener
import androidx.activity.result.contract.ActivityResultContracts
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat
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

        val launcher = registerForActivityResult(ActivityResultContracts.RequestPermission()) { granted ->
            binding.ffmpegButton.isEnabled = granted
            binding.mediaButton.isEnabled = granted
        }
        val permission = when
        {
            Build.VERSION.SDK_INT >= Build.VERSION_CODES.UPSIDE_DOWN_CAKE ->
            {
                if (ContextCompat.checkSelfPermission(this, Manifest.permission
                    .READ_MEDIA_VISUAL_USER_SELECTED) == PackageManager.PERMISSION_GRANTED)
                    Manifest.permission.READ_MEDIA_VISUAL_USER_SELECTED else
                        Manifest.permission.READ_MEDIA_VIDEO
            }
            Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU -> Manifest.permission.READ_MEDIA_VIDEO
            else -> Manifest.permission.READ_EXTERNAL_STORAGE
        }
        launcher.launch(permission)

        binding.ffmpegButton.setOnClickListener(this)
        binding.mediaButton.setOnClickListener(this)
    }

    override fun onClick(v: View)
    {
        when (v.id)
        {
            R.id.ffmpeg_button -> startActivity(Intent(this, FFmpegActivity::class.java))
            R.id.media_button -> {}
        }
    }
}