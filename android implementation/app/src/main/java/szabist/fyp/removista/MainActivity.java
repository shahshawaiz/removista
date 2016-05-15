package szabist.fyp.removista;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.hardware.Camera;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceView;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.WindowManager;
import android.view.View.OnTouchListener;
import android.widget.Toast;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;
import org.opencv.video.BackgroundSubtractor;
import org.opencv.video.Video;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

//public class MainActivity extends Activity implements CvCameraViewListener2{
public class MainActivity extends Activity implements CvCameraViewListener2, OnTouchListener{
    private static final String TAG = "Removista::MainActivity";

    static{
        //helper method, check if opencv loaded
      if(!OpenCVLoader.initDebug()){
          Log.i("Removsita", "Initilzization failed");
      }else{
          Log.i("Removsita", "Initilzization succeded");
      }
    }

    public MainActivity() {
        Log.i("Removsita", "Instantiated new " + this.getClass());
    }

    //opencv dedicated camera
    protected CameraViewActivity mOpenCvCameraView;
    //protected CameraBridgeViewBase mOpenCvCameraView;

    // variable initializatio
        //frames
        private Mat rgba; //mat with alpha
        private Mat rgb; //mat without alpha
        private Mat fg_mask;
        private Mat history[];
        private int index = 0;
        private List<Camera.Size> mResolutionList;

        //backgground segmentation
        private BackgroundSubtractor sub; //background subtractor
        private final int history_size = 50;
        private final float thresold = 0;
        private final boolean detect_shadows = true;

    //opencv manager call
    private BaseLoaderCallback mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS:{
                    Log.i("opencv", "OpenCV loaded successfully");
                    mOpenCvCameraView.enableView();
                    mOpenCvCameraView.setOnTouchListener(MainActivity.this);
                } break;
                default:{
                    super.onManagerConnected(status);
                } break;
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // keep cmamera open
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        //bin content layout to following class
        setContentView(R.layout.activity_main);

        // get hangle of camera
        mOpenCvCameraView = (CameraViewActivity) findViewById(R.id.camera_canvas);
        //mOpenCvCameraView = (CameraBridgeViewBase) findViewById(R.id.camera_canvas);

        //set visibility
        mOpenCvCameraView.setVisibility(SurfaceView.VISIBLE);
        mOpenCvCameraView.setCvCameraViewListener(this);

        // enable camera
        mOpenCvCameraView.enableView();
        mOpenCvCameraView.setOnTouchListener(MainActivity.this);

        Toast.makeText(this, "Tap to capture!", Toast.LENGTH_LONG).show();
    }

    @Override
    public void onResume()
    {
        super.onResume();

        //enable camera view thread application is resumed
        mOpenCvCameraView.enableView();
    }

    @Override
    public void onPause()
    {
        super.onPause();

        //disable camera when application thread is paused
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    public void onDestroy() {
        super.onDestroy();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    public void onCameraViewStarted(int width, int height) {
        sub= Video.createBackgroundSubtractorMOG2(history_size, thresold, detect_shadows);
        rgba = new Mat(height, width, CvType.CV_8UC4);
        rgb = new Mat(height, width, CvType.CV_8UC4);
        fg_mask = new Mat(height, width, CvType.CV_8UC1);
        history= new Mat[1000];
    }

    public void onCameraViewStopped() {
        rgba.release();
        rgb.release();
        fg_mask.release();

    }

    public Mat onCameraFrame(CameraBridgeViewBase.CvCameraViewFrame inputFrame) {
        //current frame's rgba
        rgba = inputFrame.rgba();

        history[index] = new Mat(3, 3, CvType.CV_64FC1 );

        // convert rgba to rgb
        Imgproc.cvtColor(rgba, rgb, Imgproc.COLOR_RGBA2RGB);

        rgba.copyTo(history[index]);

        if(index==999){
            index=10;
        }

        if(index > 10) {
            // apply background subtraction
            sub.apply(rgb, fg_mask);

            Imgproc.equalizeHist(fg_mask, fg_mask);
            Imgproc.medianBlur(fg_mask, fg_mask, 5);

            history[index-10].copyTo(rgba, fg_mask);

            return rgba;
        }

        index++;

        return null;
    }

    @SuppressLint("SimpleDateFormat")
    @Override
    public boolean onTouch(View v, MotionEvent event) {
        Toast.makeText(this, "Tapped!", Toast.LENGTH_SHORT).show();

        Log.i(TAG, "onTouch event");
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd_HH-mm-ss");
        String currentDateandTime = sdf.format(new Date());
        String fileName = Environment.getExternalStorageDirectory().getPath() +
                "/sample_picture_" + currentDateandTime + ".jpg";

        Imgcodecs.imwrite(fileName, rgba);

        //mOpenCvCameraView.takePicture(fileName);
        Toast.makeText(this, fileName + " saved", Toast.LENGTH_SHORT).show();
        return false;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }



}
