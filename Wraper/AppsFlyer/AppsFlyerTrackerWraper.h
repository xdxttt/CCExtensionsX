#pragma once
#include <map>

// In app event names constants
#define WraperAFEventLevelAchieved            "af_level_achieved"
#define WraperAFEventAddPaymentInfo           "af_add_payment_info"
#define WraperAFEventAddToCart                "af_add_to_cart"
#define WraperAFEventAddToWishlist            "af_add_to_wishlist"
#define WraperAFEventCompleteRegistration     "af_complete_registration"
#define WraperAFEventTutorial_completion      "af_tutorial_completion"
#define WraperAFEventInitiatedCheckout        "af_initiated_checkout"
#define WraperAFEventPurchase                 "af_purchase"
#define WraperAFEventRate                     "af_rate"
#define WraperAFEventSearch                   "af_search"
#define WraperAFEventSpentCredits             "af_spent_credits"
#define WraperAFEventAchievementUnlocked      "af_achievement_unlocked"
#define WraperAFEventContentView              "af_content_view"
#define WraperAFEventListView                 "af_list_view"
#define WraperAFEventTravelBooking            "af_travel_booking"
#define WraperAFEventShare                    "af_share"
#define WraperAFEventInvite                   "af_invite"
#define WraperAFEventLogin                    "af_login"
#define WraperAFEventReEngage                 "af_re_engage"
#define WraperAFEventUpdate                   "af_update"
#define WraperAFEventOpenedFromPushNotification "af_opened_from_push_notification"
#define WraperAFEventLocation                 "af_location_coordinates"

// In app event parameter names
#define WraperAFEventParamLevel                  "af_level"
#define WraperAFEventParamScore                  "af_score"
#define WraperAFEventParamSuccess                "af_success"
#define WraperAFEventParamPrice                  "af_price"
#define WraperAFEventParamContentType            "af_content_type"
#define WraperAFEventParamContentId              "af_content_id"
#define WraperAFEventParamContentList            "ad_content_list"
#define WraperAFEventParamCurrency               "af_currency"
#define WraperAFEventParamQuantity               "af_quantity"
#define WraperAFEventParamRegistrationMethod     "af_registration_method"
#define WraperAFEventParamPaymentInfoAvailable   "af_payment_info_available"
#define WraperAFEventParamMaxRatingValue         "af_max_rating_value"
#define WraperAFEventParamRatingValue            "af_rating_value"
#define WraperAFEventParamSearchString           "af_search_string"
#define WraperAFEventParamDateA                  "af_date_a"
#define WraperAFEventParamDateB                  "af_date_b"
#define WraperAFEventParamDestinationA           "af_destination_a"
#define WraperAFEventParamDestinationB           "af_destination_b"
#define WraperAFEventParamDescription            "af_description"
#define WraperAFEventParamClass                  "af_class"
#define WraperAFEventParamEventStart             "af_event_start"
#define WraperAFEventParamEventEnd               "af_event_end"
#define WraperAFEventParamLat                    "af_lat"
#define WraperAFEventParamLong                   "af_long"
#define WraperAFEventParamCustomerUserId         "af_customer_user_id"
#define WraperAFEventParamValidated              "af_validated"
#define WraperAFEventParamRevenue                "af_revenue"
#define WraperAFEventParamReceiptId              "af_receipt_id"
#define WraperAFEventParam1                      "af_param_1"
#define WraperAFEventParam2                      "af_param_2"
#define WraperAFEventParam3                      "af_param_3"
#define WraperAFEventParam4                      "af_param_4"
#define WraperAFEventParam5                      "af_param_5"
#define WraperAFEventParam6                      "af_param_6"
#define WraperAFEventParam7                      "af_param_7"
#define WraperAFEventParam8                      "af_param_8"
#define WraperAFEventParam9                      "af_param_9"
#define WraperAFEventParam10                     "af_param_10"

class AppsFlyerTrackerWraper{
public:
    AppsFlyerTrackerWraper();
    ~AppsFlyerTrackerWraper();
    static AppsFlyerTrackerWraper *getInstance();
    static void destroyInstance();
    
   // void trackEvent(std::string event,std::string value);
    void trackEvent(std::string event,std::map<std::string,std::string> values);
    
};

