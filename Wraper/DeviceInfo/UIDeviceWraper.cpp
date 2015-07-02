#include "UIDeviceWraper.h"

#if(CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
//TODO Add Android And WinPhone
UIDeviceWraper::UIDeviceWraper(void) {
}

UIDeviceWraper::~UIDeviceWraper(void) {
  
}

std::string  UIDeviceWraper::getUUID(){
    char temp[128]={0};
    long seconds= time((time_t*)NULL);
    sprintf(temp,"AD%ld/n",seconds);
    return temp;
}

std::string UIDeviceWraper::getUDID() {
    try{
        android.telephony.TelephonyManager tm = (android.telephony.TelephonyManager) context
        .getSystemService(Context.TELEPHONY_SERVICE);
        String device_id = tm.getDeviceId();
        android.net.wifi.WifiManager wifi = (android.net.wifi.WifiManager) context.getSystemService(Context.WIFI_SERVICE);
        String mac = wifi.getConnectionInfo().getMacAddress();
        if( TextUtils.isEmpty(device_id) ){
            device_id = mac;
        }
        if( TextUtils.isEmpty(device_id) ){
            device_id = android.provider.Settings.Secure.getString(context.getContentResolver(),android.provider.Settings.Secure.ANDROID_ID);
        }
        return device_id.toString();
    }catch(Exception e){
        e.printStackTrace();
    }
}

std::string UIDeviceWraper::getName(){
    char temp[128]={0};
    long seconds= time((time_t*)NULL);
    sprintf(temp,"AD%ld/n",seconds);
    return temp;
}
std::string  UIDeviceWraper::getModel(){
  return "androidModel";
}

std::string  UIDeviceWraper::getLocalizedModel(){
    return "androidLocalized";
}

std::string  UIDeviceWraper::getSystemName(){
    return "andrido";
}

std::string  UIDeviceWraper::getSystemVersion(){
    return "andrido";
}
#endif
