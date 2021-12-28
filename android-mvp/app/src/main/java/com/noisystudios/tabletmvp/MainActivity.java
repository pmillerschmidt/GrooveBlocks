package com.noisystudios.tabletmvp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class MainActivity extends AppCompatActivity {

    @BindView(R.id.bFreeStyle)
    Button bFreeStyle;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);
    }

    @OnClick(R.id.bFreeStyle)
    public void clickFreeStyle() {
        Intent intent = new Intent(MainActivity.this, FreeStyleActivity.class);
        startActivity(intent);
    }
}