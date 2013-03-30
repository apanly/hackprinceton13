package com.example.android;

import android.app.Activity;
import android.content.Context;
import android.media.MediaRecorder;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.text.format.Formatter;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ProgressBar;

import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Date;

public class Home extends Activity {
    final static private String LOG_TAG = "SINGDATSHIT_MAIN";

    private MediaRecorder recorder;
    private String fileName;
    private String appDirectoryPath;
    private long startTime;
    private Button recordButton;
    private DataOutputStream outToServer;
    private Socket client;
    private BufferedReader inFromServer;
    private Handler handler;
    private ProgressBar volume;

    private TextView textView;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        appDirectoryPath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/singdatshit/";
        new File(appDirectoryPath).mkdirs();
        LinearLayout layout = new LinearLayout(this);
        textView = new TextView(this);
        recordButton = new Button(this);
        volume = new ProgressBar(this);
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
        Button sendshitButton = new Button(this);
        sendshitButton.setText("sendshit");
        sendshitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                new SendMessageAsyncTask().execute();
//                Log.e(LOG_TAG, "fuckfuckfuck");
            }
        });
        layout.addView(textView);
        layout.addView(recordButton);
        layout.addView(sendshitButton);
        layout.addView(volume);
        setContentView(layout);
//        enableConnection();
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
        volume.setMax(recorder.getAudioSourceMax());
        
        handler = new Handler();
        handler.post(new Runnable {
        	
        	public void run() {
        		//display shit
        		
        		
        		
        		volume.setProgress(recorder.getMaxAmplitude());
        		
        		handler.postDelayed(this, 75);
        	}
        });
    }

    private void stopRecording() {
        recordButton.setText("Start recording");
        recorder.stop();
        recorder.release();
        recorder = null;
        handler = null;
//        new AddToDropboxTask().execute(fileName.concat(".mp4"));
    }

    private String getLocalIpAddress() {

        WifiManager wifi = (WifiManager) getSystemService(Context.WIFI_SERVICE);

        // Get WiFi status
        WifiInfo info = wifi.getConnectionInfo();

        return Formatter.formatIpAddress(info.getIpAddress());
    }

    private void setUpIOStreams() throws IOException
    {
//        Log.e(LOG_TAG, "asdlfkj0");
        InetAddress addr = InetAddress.getByName("10.24.142.176");
                //ipBox.getText().toString());

//        Log.e(LOG_TAG, "asdlfkj1");

        try {
            //client = new Socket(addr, 8887);
//            client = new Socket("10.24.142.176", 5252);
            client = new Socket("unix3.andrew.cmu.edu", 8888);
//            client = new Socket("localhost", 8887);
        } catch (Throwable e) {
//            Log.e(LOG_TAG, "98q3y4qxw8rybq98xy3r98yq384bcto");
            Log.e(LOG_TAG, e.getMessage());
        }
//        Log.e(LOG_TAG, "asdlfkj2");

        outToServer = new DataOutputStream(client.getOutputStream());
//        Log.e(LOG_TAG, "asdlfkj3");

        inFromServer = new BufferedReader(
                new InputStreamReader(
                        client.getInputStream()));
//        Log.e(LOG_TAG, "asdlfkj4");
    }

    private void enableConnection()
    {
        try {
            setUpIOStreams();
            String ip = client.getInetAddress().toString();

//            setText(textView,"Device's IP Address: " + ipAddress);
            Log.e(LOG_TAG, "Device's IP Address: " + getLocalIpAddress());
            Log.e(LOG_TAG, "Server's IP Address: " + ip.substring(1));
//            setText(msgBoxHint, "Say something...");
//            setText(appendText, "Enter your message then press the send button");

//            setValues(R.id.connect,true);
//            setValues(R.id.send,true);
//            setValues(R.id.ipBox,false);
//            setValues(R.id.msgBox,true);
        } catch (IOException e) {

//            setValues(R.id.connect,false);
            Log.e(LOG_TAG, "didn't connect");
            Toast.makeText(this, e.toString(), Toast.LENGTH_LONG).show();
        }
    }

    private void disableConnection()
    {
        if(client != null)
        {
            try {
                client.close();
            } catch (IOException e) {
                Toast.makeText(this, e.toString(), Toast.LENGTH_LONG).show();
            }

//            setText(R.id.text,"Press the connect button to start the client");
//            setText(R.id.msgBox,"");
//            setText(msgBoxHint,"");
//
//            setValues(R.id.connect,false);
//            setValues(R.id.ipBox,true);
//            setValues(R.id.msgBox,false);
//            setValues(R.id.send,false);
        }
        else
        {
//            setValues(R.id.connect,false);
        }
    }

    private void sendDataOverConnection()
    {
        InputStream inputStream;
        try {
            inputStream = new FileInputStream(new File(appDirectoryPath+fileName+".wav"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
            Log.e(LOG_TAG, "FUCK THIS SHIT");
            return;
        }
        String sentence = "helo\n";
        try {
            if (client == null || client.isClosed()) setUpIOStreams();

            Log.e(LOG_TAG, "wtf");
            byte[] b = new byte[32678];
            while (inputStream.read(b) > 0) {
                outToServer.write(b);
            }

//            outToServer.writeBytes(sentence);
//            Log.e(LOG_TAG, "ok wrote message");
            String modifiedSentence = inFromServer.readLine();
//            Log.e(LOG_TAG, "ok read message");

//            sentence = ("OUT TO SERVER: " + sentence);
            sentence += "\n" +("IN FROM SERVER: " + modifiedSentence);
            Log.e(LOG_TAG, "message: "+modifiedSentence);

            client.close();

        } catch (IOException e) {
            Toast.makeText(this, e.toString(), Toast.LENGTH_LONG).show();
            Log.e(LOG_TAG, "ok did not sent message");

//            setValues(R.id.ipBox,true);
//            setValues(R.id.connect,false);
//            setValues(R.id.send,false);
//            setValues(R.id.msgBox,false);
        }
//        setText(appendText, sentence);
    }

    public class OpenSocketAsyncTask extends AsyncTask<Void,Void,Void> {
        @Override
        protected Void doInBackground(Void... voids) {
            try {
                setUpIOStreams();
            } catch (IOException e) {
                Log.e(LOG_TAG, e.getStackTrace().toString());  //To change body of catch statement use File | Settings | File Templates.
            }
            return null;
        }
    }

    public class SendMessageAsyncTask extends AsyncTask<Void,Void,Void> {
        @Override
        protected Void doInBackground(Void... voids) {
//            Log.e(LOG_TAG, "weprebqisidnjciwebirwei waef");
            sendDataOverConnection();
            return null;
        }
    }
    
    
}
