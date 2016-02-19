package com.malom.ccextensions;

import java.util.Arrays;
import java.util.List;

import org.util.*;

import android.app.Activity;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class GoogleIabWraper {
	public static class PurchaseFlowPack {
		public int rc;
		public String payload;
		public String sku;
	}

	public static IabHelper mHelper;
	static final String TAG = "GoogleIabWraper";
	private static final int HANDLER_queryInventory = 0;
	private static final int HANDLER_launchPurchaseFlow = 1;
	private static final int HANDLER_consumeAsync = 2;
	private static final int HANDLER_startSetup = 4;

	static Activity mActive;
	static Handler mHandler;

	public static void init(Activity active) {
		mActive = active;
		mHandler = new Handler() {
			public void handleMessage(Message msg) {
				switch (msg.what) {
				case GoogleIabWraper.HANDLER_startSetup:
					startSetupHandler();
					break;
				case GoogleIabWraper.HANDLER_queryInventory:
					queryInventoryHandler((List<String>) msg.obj);
					break;
				case GoogleIabWraper.HANDLER_launchPurchaseFlow:
					launchPurchaseFlowHandler(((PurchaseFlowPack) msg.obj).sku, ((PurchaseFlowPack) msg.obj).rc,
							((PurchaseFlowPack) msg.obj).payload);
					break;
				case GoogleIabWraper.HANDLER_consumeAsync:
					consumeAsyncHandler((Purchase) msg.obj);
					break;
				}
			}
		};

	}

	public static void startSetup() {
		Message msg = new Message();
		msg.what = HANDLER_startSetup;
		GoogleIabWraper.mHandler.sendMessage(msg);
	}

	public static void queryInventory(String[] skus) {
		List<String> skulist = Arrays.asList(skus);
		Message msg = new Message();
		msg.what = HANDLER_queryInventory;
		msg.obj = skulist;
		GoogleIabWraper.mHandler.sendMessage(msg);
	}

	public static void launchPurchaseFlow(String sku, int rc, String payload) {
		Message msg = new Message();
		PurchaseFlowPack pack = new PurchaseFlowPack();
		pack.sku = sku;
		pack.rc = rc;
		pack.payload = payload;
		msg.what = HANDLER_launchPurchaseFlow;
		msg.obj = pack;

		GoogleIabWraper.mHandler.sendMessage(msg);
	}

	public static void consumeAsync(Purchase purchase) {
		Message msg = new Message();
		msg.what = HANDLER_consumeAsync;
		msg.obj = purchase;
		GoogleIabWraper.mHandler.sendMessage(msg);
	}

	public static void startSetupHandler() {
		// String base64EncodedPublicKey =
		// "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAtf0kURiCCZoNkpF9OddE67QBxx+O/eXQ7m6oYN6RJ60HDdTc6+GHS5DeoswoA0kxZndwseNTQ8IlSNpf4WIm+7bp+1tZEvLDpM97A/XIY5+S2pKuwysdADCOP6VnBqNUwX94sDp8OzvrmyCkTBOG8EpMPymLdeJaFeS8Kx3m8dDj6V6tB59GdmYWd5IGxDCLoHiLKV9wS3mdSfq7nW8SLah6pr9EyBpyaXuj6wh6iZS4mnCiUdVz1KuxHUizopt9yHaXb1FHQigfmB7JuxsW1eGlnceB4D8WEVeIm1FRChPexxNjIzWRhKGb31p1HpS8/r8eEcn4C3ezE9mjnn+YUwIDAQAB";
		String base64EncodedPublicKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAoP1iZGeDjy2bnRKXsyp1hOy+L3S2ws3yq78LNW4u8AMekm4qt0lpj196Dk6eOFfHwgl/IudSArvgDl3ltoH6ldQHb2wTLbk+SIbDeHe7Q2Y2joQamkVIgSnMH6FQ5WBdWGkAUhwADpQsFdLS+/1t/Mx2LQUxmyxzhCwKAEAD0xnPESFO6B3ZFeiX85/l4snfjSIBQp1h+O6FPxYbxiPmxkxSgGwRbkJgDq0SZdLYDKj53YXgWcOjkDrCP7TY76nVSSJMiUOtmBh4Wg+GLIxQzMrQmBGL51nUNCXlFxbOqO9PUugpJj8temOO73Sk869T+oK239sYbba4V1Am+S8ZaQIDAQAB";
		mHelper = new IabHelper(mActive, base64EncodedPublicKey);
		mHelper.startSetup(mOnIabSetupFinishedListener);
		mHelper.enableDebugLogging(true);
	}

	public static void queryInventoryHandler(List<String> skulist) {
		mHelper.queryInventoryAsync(true, skulist, mGotInventoryListener);
	}

	public static void launchPurchaseFlowHandler(String sku, int rc, String payload) {
		if (mHelper == null)
			return;
		mHelper.launchPurchaseFlow(mActive, sku, rc, mPurchaseFinishedListener, payload);
	}

	public static void consumeAsyncHandler(Purchase purchase) {
		Log.d(TAG, "Consumption finished. Purchase: " + purchase);
		if (mHelper == null)
			return;
		mHelper.consumeAsync(purchase, mConsumeFinishedListener);
	}

	public static native void OnIabSetupFinishedListener(IabResult result);

	static IabHelper.OnIabSetupFinishedListener mOnIabSetupFinishedListener = new IabHelper.OnIabSetupFinishedListener() {
		public void onIabSetupFinished(IabResult result) {
			Log.d(TAG, "SetupFinished finished.");
			if (mHelper == null)
				return;
			OnIabSetupFinishedListener(result);
		}
	};

	public static native void QueryInventoryFinishedListener(IabResult result, Inventory inventory);

	static IabHelper.QueryInventoryFinishedListener mGotInventoryListener = new IabHelper.QueryInventoryFinishedListener() {
		public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
			Log.d(TAG, "Query inventory finished.");
			if (mHelper == null)
				return;
			QueryInventoryFinishedListener(result, inventory);
		}
	};

	public static native void OnIabPurchaseFinishedListener(IabResult result, Purchase purchase);

	static IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener = new IabHelper.OnIabPurchaseFinishedListener() {
		public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
			Log.d(TAG, "Purchase finished: " + result + ", purchase: " + purchase);
			if (mHelper == null)
				return;
			OnIabPurchaseFinishedListener(result, purchase);
		}
	};

	public static native void OnConsumeFinishedListener(IabResult result, Purchase purchase);

	static IabHelper.OnConsumeFinishedListener mConsumeFinishedListener = new IabHelper.OnConsumeFinishedListener() {
		public void onConsumeFinished(Purchase purchase, IabResult result) {
			Log.d(TAG, "Consumption finished. Purchase: " + purchase + ", result: " + result);
			if (mHelper == null)
				return;
			OnConsumeFinishedListener(result, purchase);
		}
	};

}
