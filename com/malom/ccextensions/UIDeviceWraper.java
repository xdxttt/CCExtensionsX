package com.malom.ccextensions;
import java.util.Locale;
import java.util.Random;
import java.util.UUID;

import android.app.Activity;
import android.content.Context;
import android.telephony.TelephonyManager;
public class UIDeviceWraper {
	public static String udid = "";
	public static void init(Activity active){
		final TelephonyManager tm = (TelephonyManager)  active.getBaseContext().getSystemService(Context.TELEPHONY_SERVICE);
		final String tmDevice, tmSerial, androidId;
		tmDevice = "" + tm.getDeviceId();
		tmSerial = "" + tm.getSimSerialNumber();
		androidId = "" + android.provider.Settings.Secure.getString( active.getContentResolver(), android.provider.Settings.Secure.ANDROID_ID);
		UUID deviceUuid = new UUID(androidId.hashCode(), ((long)tmDevice.hashCode() << 32) | tmSerial.hashCode());
		udid = deviceUuid.toString();
	}
	
	public static String getUDID(){
		return udid;
	}
    public static String getUUID(){
    	return udid;
    }
    public static String getName(){
    	Random random = new Random();
		String ret = android.os.Build.MANUFACTURER;
		ret += String.valueOf(random.nextInt(200));
		ret += String.valueOf(random.nextInt(200));
		ret += String.valueOf(random.nextInt(200));
		return ret;
    }
    public static String getModel(){
    	return android.os.Build.MODEL;
    }
    public static String getLocalizedModel(){
    	return  android.os.Build.PRODUCT;
    }
    public static String getSystemName(){
    	return android.os.Build.MANUFACTURER;
    }
    public static String getSystemVersion(){
    	return android.os.Build.VERSION.SDK_INT+"";
    }
	public static String getDefaultLanguage(){
		return Locale.getDefault().getLanguage();
	}
}
