package com.malom.ccextensions;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;

public class AppInfo {
	public static String version = "";
	public static String build = "";
	public static void init(Context context){
		PackageManager packageManager = context.getPackageManager();
		PackageInfo packageInfo;
		try {
			packageInfo = packageManager.getPackageInfo("com.tjgame.PuzzleWarriorOnline", 0);
			version = packageInfo.versionName;
			build = packageInfo.versionName;
		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}
	}
	public static String getVersion(){
		return version;
	}
	public static String getBuild(){
		return build;
	}
}
