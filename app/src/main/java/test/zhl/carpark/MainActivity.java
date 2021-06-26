package test.zhl.carpark;


import android.app.NativeActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.widget.TextView;


public class MainActivity extends NativeActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

    }

    @Override
    public boolean dispatchTouchEvent(MotionEvent ev) {

        Log.d("MyEgl", "dispatchTouchEvent");

        return super.dispatchTouchEvent(ev);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        Log.d("MyEgl", "onTouchEvent");

        return super.onTouchEvent(event);
    }
}