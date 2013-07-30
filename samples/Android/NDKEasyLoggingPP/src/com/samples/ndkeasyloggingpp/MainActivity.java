package com.samples.ndkeasyloggingpp;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.TextView;

public class MainActivity extends Activity {

	TextView txtEdit;
	
	static {
		System.loadLibrary("EasyLoggingTest");
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		txtEdit = (TextView)findViewById(R.id.textView1);
		txtEdit.setText(messageFromNative());
		
		try {
			FileOutputStream fOut = openFileOutput("samplefile.txt",
			        MODE_WORLD_READABLE);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	public native String messageFromNative();
		
	
}
