package szabist.fyp.removista;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;

import com.github.paolorotolo.appintro.AppIntro;
import com.github.paolorotolo.appintro.AppIntroFragment;

public class WalkthroughActivity extends AppIntro {

    // Please DO NOT override onCreate. Use init.
    @Override
    public void init(Bundle savedInstanceState) {

        // Add your slide's fragments here.
        // AppIntro will automatically generate the dots indicator and buttons.
//        addSlide(first_fragment);

        // Instead of fragments, you can also use our default slide
        // Just set a title, description, background and image. AppIntro will do the rest.
        addSlide(AppIntroFragment.newInstance("REMOVISTA", "The ultimate obstruction removal tool for crowded scene photography.", R.drawable.intro, Color.parseColor("#2196F3"), Color.parseColor("#ffffff"),Color.parseColor("#ffffff")));
        addSlide(AppIntroFragment.newInstance("AIM", "Aim your target, make sure that camera doesn't move", R.drawable.aim, Color.parseColor("#E91E63"), Color.parseColor("#ffffff"),Color.parseColor("#ffffff")));
        addSlide(AppIntroFragment.newInstance("WAIT", "Wait for the right moment", R.drawable.wait, Color.parseColor("#009688"), Color.parseColor("#ffffff"),Color.parseColor("#ffffff")));
        addSlide(AppIntroFragment.newInstance("TAP", "and Capture your moment by tapping on screen", R.drawable.tap, Color.parseColor("#B71C1C"), Color.parseColor("#ffffff"),Color.parseColor("#ffffff")));
        addSlide(AppIntroFragment.newInstance("HAVE FUN!", "Find captured image in files directory of your android device.", R.drawable.location, Color.parseColor("#880E4F"), Color.parseColor("#ffffff"),Color.parseColor("#ffffff")));

        // OPTIONAL METHODS
        // Override bar/separator color.
        setBarColor(Color.parseColor("#000000"));
        setSeparatorColor(Color.parseColor("#2196F3"));

        // Hide Skip/Done button.
        showSkipButton(true);
        setProgressButtonEnabled(true);

        setFadeAnimation();

        // Turn vibration on and set intensity.
        // NOTE: you will probably need to ask VIBRATE permisssion in Manifest.
    }

    @Override
    public void onSkipPressed() {
        // Do something when users tap on Skip button.
        Intent i = new Intent(getBaseContext(),MainActivity.class);
        startActivity(i);
    }

    @Override
    public void onDonePressed() {
        // Do something when users tap on Done button.
        Intent i = new Intent(getBaseContext(),MainActivity.class);
        startActivity(i);
    }

    @Override
    public void onSlideChanged() {
        // Do something when the slide changes.
    }

    @Override
    public void onNextPressed() {
        // Do something when users tap on Next button.
    }

}
