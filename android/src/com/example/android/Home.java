package com.example.android;

import android.app.Activity;
import android.media.MediaRecorder;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.Toast;

import java.io.IOException;
import java.util.Date;

public class Home extends Activity {
    final static private String LOG_TAG = "SINGDATSHIT_MAIN";

    private MediaRecorder recorder;
    private String fileName;
    private String appDirectoryPath;
    private long startTime;
    private Button recordButton;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        appDirectoryPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/recordat/";
        LinearLayout layout = new LinearLayout(this);
        recordButton = new Button(this);
        layout.addView(recordButton);
        setContentView(layout);
    }

    private void onRecord(boolean start) {
        if (start) {
            startRecording();
        } else {
            stopRecording();
        }
    }

    private void startRecording() {
        fileName = new Date().getTime() + "";
        recorder = new MediaRecorder();
        recorder.setAudioSource(MediaRecorder.AudioSource.MIC);
        recorder.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP);
        recorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB);
        recorder.setOutputFile(appDirectoryPath + fileName + ".wav");

        try {
            recorder.prepare();
            recorder.start();
            startTime = new Date().getTime();
        } catch (IOException e) {
            Log.e(LOG_TAG, "prepare() failed");
            Toast.makeText(this, "fuck, we are not prepared", Toast.LENGTH_LONG).show();
        }
    }

    private void stopRecording() {
        recordButton.setText("Start recording");
        recorder.stop();
        recorder.release();
        recorder = null;
//        new AddToDropboxTask().execute(fileName.concat(".mp4"));
    }
}
