package com.malom.ccextensions;

import java.util.Arrays;
import java.util.List;

import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.login.LoginManager;
import com.facebook.login.LoginResult;
import android.app.Activity;

public class FBSDKLoginManagerWraper {
    static final String TAG = "FBSDKLoginManagerWraper";

	static Activity mActive;
    public static CallbackManager mCallbackManager = null;
    public static native void onLoginSuccess(LoginResult loginResult);
    public static native void onLoginCancel();
    public static native void onLoginError(String error);
    
	public static void init(Activity active){
		FBSDKLoginManagerWraper.mActive = active;
		    mCallbackManager = CallbackManager.Factory.create();
		    LoginManager.getInstance().registerCallback(mCallbackManager,
		            new FacebookCallback<LoginResult>() {
		                @Override
		                public void onSuccess(LoginResult loginResult) {
		                	onLoginSuccess(loginResult);
		                }

		                @Override
		                public void onCancel() {
		                	onLoginCancel();
		                }

		                @Override
		                public void onError(FacebookException exception) {
		                	onLoginError(exception.toString());  
		                }
		    });
	}
    public static void logInWithPublishPermissions(String[] permissions){
		List<String> permissionsList = Arrays.asList(permissions);  
	    LoginManager.getInstance().logInWithPublishPermissions(mActive,permissionsList);
    }
	public static void logInWithReadPermissions(String[] permissions){
		List<String> permissionsList = Arrays.asList(permissions);  
	    LoginManager.getInstance().logInWithReadPermissions(mActive,permissionsList);
	}

}
