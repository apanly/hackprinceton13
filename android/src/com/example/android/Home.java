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

import java.io.File;
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
        appDirectoryPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/singdatshit/";
        new File(appDirectoryPath).mkdirs();
        LinearLayout layout = new LinearLayout(this);
        recordButton = new Button(this);
        recordButton.setText("RECORD THAT SHIT!");
        recordButton.setOnClickListener(new View.OnClickListener() {
            private boolean startBool = true;
            @Override
            public void onClick(View view) {
                if (startBool) {
                    startRecording();
                    recordButton.setText("STOP RECORDING THAT SHIT!");
                    startBool = false;
                } else {
                    stopRecording();
                    recordButton.setText("RECORD THAT SHIT!");
                    startBool = true;
                }
            }
        });
        layout.addView(recordButton);
        setContentView(layout);
    }

    private void startRecording() {
        fileName = new Date().getTime() + "";
        recorder = new MediaRecorder();
        recorder.setAudioSource(MediaRecorder.AudioSource.MIC);
        recorder.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP);
        recorder.setOutputFile(appDirectoryPath + fileName + ".wav");
        recorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB);

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
