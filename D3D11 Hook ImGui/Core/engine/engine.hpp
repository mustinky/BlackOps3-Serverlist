
#include "../../pch.h"

#ifndef ENGINE_H
#define ENGINE_H

class Engine
{

public:

	static std::uintptr_t offset(std::uintptr_t offset)
	{
		std::uintptr_t original_offset = spoof_call(offset);

		HMODULE module_handle = GetModuleHandleA(nullptr);

		if (module_handle == nullptr)
			return 0;

		return reinterpret_cast<std::uintptr_t>(module_handle) + original_offset;
	}

private:

	static constexpr unsigned int compute_spoof_call()
	{
		constexpr unsigned int call_one = 0xDEAD;
		constexpr unsigned int call_two = 0xBEEF; 

		return (call_one << 16) | call_two;
	}

	static std::uintptr_t spoof_call(std::uintptr_t offset)
	{
		constexpr unsigned int spoof =
			(0xABCD1234 ^ compute_spoof_call()) ^ 0xABCD1234;

		return offset ^ spoof;
	}
};

namespace structures
{
	enum Enum1
	{
		INVALID = 0xFFFFFFFF,
		FIRST = 0x0,
		INDEX_0 = 0x0,
		INDEX_1 = 0x1,
		INDEX_2 = 0x2,
		INDEX_3 = 0x3,
		COUNT = 0x4,
	};

    enum QueryId
    {
        SEARCH_SESSIONS_INVALID = 0x0,
        SEARCH_SESSIONS_BY_PLAYLIST_VERSION = 0x1,
        SEARCH_SESSIONS = 0x2,
        SEARCH_SESSION_BY_GAME_SECURITY_ID = 0x3,
        SEARCH_SESSION_DEDICATED = 0x4,
        SEARCH_SESSIONS_DEDICATED_PARKED = 0x5,
        SEARCH_SESSIONS_BY_SERVER_TYPE = 0x6,
    };

    enum netadrtype_t
    {
        NA_BOT = 0x0,
        NA_BAD = 0x1,
        NA_LOOPBACK = 0x2,
        NA_RAWIP = 0x3,
        NA_IP = 0x4,
    };

    enum netsrc_t
    {
        NS_NULL = 0xFFFFFFFF,
        NS_CLIENT1 = 0x0,
        NS_CLIENT2 = 0x1,
        NS_CLIENT3 = 0x2,
        NS_CLIENT4 = 0x3,
        NS_SERVER = 0x4,
        NS_MAXCLIENTS = 0x4,
        NS_PACKET = 0x5,
    };

    enum LobbyType
    {
        LOBBY_TYPE_INVALID = 0xFFFFFFFF,
        LOBBY_TYPE_PRIVATE = 0x0,
        LOBBY_TYPE_GAME = 0x1,
        LOBBY_TYPE_TRANSITION = 0x2,
        LOBBY_TYPE_COUNT = 0x3,
        LOBBY_TYPE_FIRST = 0x0,
        LOBBY_TYPE_LAST = 0x2,
        LOBBY_TYPE_AUTO = 0x3,
    };

    enum JoinType
    {
        JOIN_TYPE_NORMAL = 0x0,
        JOIN_TYPE_PLAYLIST = 0x1,
        JOIN_TYPE_FRIEND = 0x2,
        JOIN_TYPE_INVITE = 0x3,
        JOIN_TYPE_PARTY = 0x4,
        JOIN_TYPE_GROUPS = 0x5,
        JOIN_TYPE_COUNT = 0x6,
    };

    enum TaskState
    {
        TASK_STATE_INVALID = 0x0,
        TASK_STATE_INIT = 0x1,
        TASK_STATE_INPROGRESS = 0x2,
        TASK_STATE_INCALLBACK = 0x3,
        TASK_STATE_CHILDCOMPLETE = 0x4,
        TASK_STATE_CHILDFAILED = 0x5,
        TASK_STATE_COMPLETED = 0x6,
        TASK_STATE_FAILED = 0x7,
        TASK_STATE_CANCELLED = 0x8,
        TASK_STATE_COUNT = 0x9,
    };

	enum bdLobbyErrorCode
	{
		BD_NO_ERROR = 0x0,
		BD_TOO_MANY_TASKS = 0x1,
		BD_NOT_CONNECTED = 0x2,
		BD_SEND_FAILED = 0x3,
		BD_HANDLE_TASK_FAILED = 0x4,
		BD_START_TASK_FAILED = 0x5,
		BD_RESULT_EXCEEDS_BUFFER_SIZE = 0x64,
		BD_ACCESS_DENIED = 0x65,
		BD_EXCEPTION_IN_DB = 0x66,
		BD_MALFORMED_TASK_HEADER = 0x67,
		BD_INVALID_ROW = 0x68,
		BD_EMPTY_ARG_LIST = 0x69,
		BD_PARAM_PARSE_ERROR = 0x6A,
		BD_PARAM_MISMATCHED_TYPE = 0x6B,
		BD_SERVICE_NOT_AVAILABLE = 0x6C,
		BD_CONNECTION_RESET = 0x6D,
		BD_INVALID_USER_ID = 0x6E,
		BD_LOBBY_PROTOCOL_VERSION_FAILURE = 0x6F,
		BD_LOBBY_INTERNAL_FAILURE = 0x70,
		BD_LOBBY_PROTOCOL_ERROR = 0x71,
		BD_LOBBY_FAILED_TO_DECODE_UTF8 = 0x72,
		BD_LOBBY_ASCII_EXPECTED = 0x73,
		BD_INVALID_CONTEXT = 0x74,
		BD_LOBBY_METHOD_DISABLED = 0x75,
		BD_ASYNCHRONOUS_ERROR = 0xC8,
		BD_STREAMING_COMPLETE = 0xC9,
		BD_MEMBER_NO_PROPOSAL = 0x12C,
		BD_TEAMNAME_ALREADY_EXISTS = 0x12D,
		BD_MAX_TEAM_MEMBERSHIPS_LIMITED = 0x12E,
		BD_MAX_TEAM_OWNERSHIPS_LIMITED = 0x12F,
		BD_NOT_A_TEAM_MEMBER = 0x130,
		BD_INVALID_TEAM_ID = 0x131,
		BD_INVALID_TEAM_NAME = 0x132,
		BD_NOT_A_TEAM_OWNER = 0x133,
		BD_NOT_AN_ADMIN_OR_OWNER = 0x134,
		BD_MEMBER_PROPOSAL_EXISTS = 0x135,
		BD_MEMBER_EXISTS = 0x136,
		BD_TEAM_FULL = 0x137,
		BD_VULGAR_TEAM_NAME = 0x138,
		BD_TEAM_USERID_BANNED = 0x139,
		BD_TEAM_EMPTY = 0x13A,
		BD_INVALID_TEAM_PROFILE_QUERY_ID = 0x13B,
		BD_TEAMNAME_TOO_SHORT = 0x13C,
		BD_UNIQUE_PROFILE_DATA_EXISTS_ALREADY = 0x13D,
		BD_APPLICATION_EXISTS = 0x13E,
		BD_APPLICATIONS_MAX_EXCEEDED = 0x13F,
		BD_PAGE_SIZE_LIMIT_EXCEEDED = 0x140,
		BD_APPLICATION_REJECTED_EXISTS = 0x141,
		BD_APPLICATION_WITHDRAWN_EXISTS = 0x142,
		BD_APPLICATION_DOES_NOT_EXIST = 0x143,
		BD_APPLICATION_INVALID_STATE = 0x144,
		BD_MEMBER_BAN_EXISTS = 0x145,
		BD_MEMBER_BAN_DOES_NOT_EXIST = 0x146,
		BD_OWNER_BAN_FORBIDDEN = 0x147,
		BD_INVALID_ACCOUNT_TYPE = 0x148,
		BD_CONFIGURED_ACCOUNT_TYPE_NOT_FOUND = 0x149,
		BD_OWNER_OF_NON_EMPTY_TEAM = 0x14A,
		BD_CANNOT_APPLY_TO_PIRIVATE_TEAM = 0x14B,
		BD_MAX_NUMBER_OF_PROPOSALS_EXCEEDED = 0x14D,
		BD_MEMBER_IS_OWNER = 0x15E,
		BD_AUTO_JOINING_DISABLED = 0x15F,
		BD_TEAM_SHOWCASE_DISABLED = 0x160,
		BD_INVALID_FILTER = 0x162,
		BD_INVALID_TEAM_LEADERBOARD = 0x163,
		BD_TEAM_LEADERBOARD_LOADING = 0x164,
		BD_TEAM_SHOWCASE_COUNT_EXCEEDED = 0x165,
		BD_INVALID_LEADERBOARD_ID = 0x190,
		BD_INVALID_STATS_SET = 0x191,
		BD_EMPTY_STATS_SET_IGNORED = 0x193,
		BD_NO_DIRECT_ACCESS_TO_ARBITRATED_LBS = 0x194,
		BD_STATS_WRITE_PERMISSION_DENIED = 0x195,
		BD_STATS_WRITE_TYPE_DATA_TYPE_MISMATCH = 0x196,
		BD_NO_STATS_FOR_USER = 0x197,
		BD_INVALID_ACCESS_TO_UNRANKED_LB = 0x198,
		BD_INVALID_EXTERNAL_TITLE_ID = 0x199,
		BD_DIFFERENT_LEADERBOARD_SCHEMAS = 0x19A,
		BD_TOO_MANY_LEADERBOARDS_REQUESTED = 0x19B,
		BD_ENTITLEMENTS_ERROR = 0x19C,
		BD_ENTITLEMENTS_INVALID_TITLEID = 0x19D,
		BD_ENTITLEMENTS_INVALID_LEADERBOARDID = 0x19E,
		BD_ENTITLEMENTS_INVALID_GET_MODE_FOR_TITLE = 0x19F,
		BD_ENTITLEMENTS_URL_CONNECTION_ERROR = 0x1A0,
		BD_ENTITLEMENTS_CONFIG_ERROR = 0x1A1,
		BD_ENTITLEMENTS_NAMED_PARENT_ERROR = 0x1A2,
		BD_ENTITLEMENTS_NAMED_KEY_ERROR = 0x1A3,
		BD_TOO_MANY_ENTITY_IDS_REQUESTED = 0x1A4,
		BD_STATS_READ_FAILED = 0x1A5,
		BD_STATS_INVALID_WRITE_TO_VIRTUAL_LEADERBOARD = 0x1A6,
		BD_STATS_INVALID_WRITE_TYPE_TO_MULTIRANK_LB = 0x1A7,
		BD_INVALID_TITLE_ID = 0x1F4,
		BD_DOWN_FOR_MAINTENANCE = 0x1F5,
		BD_MESSAGING_INVALID_MAIL_ID = 0x258,
		BD_SELF_BLOCK_NOT_ALLOWED = 0x259,
		BD_GLOBAL_MESSAGE_ACCESS_DENIED = 0x25A,
		BD_GLOBAL_MESSAGES_USER_LIMIT_EXCEEDED = 0x25B,
		BD_MESSAGING_SENDER_DOES_NOT_EXIST = 0x25C,
		BD_AUTH_NO_ERROR = 0x2BC,
		BD_AUTH_BAD_REQUEST = 0x2BD,
		BD_AUTH_SERVER_CONFIG_ERROR = 0x2BE,
		BD_AUTH_BAD_TITLE_ID = 0x2BF,
		BD_AUTH_BAD_ACCOUNT = 0x2C0,
		BD_AUTH_ILLEGAL_OPERATION = 0x2C1,
		BD_AUTH_INCORRECT_LICENSE_CODE = 0x2C2,
		BD_AUTH_CREATE_USERNAME_EXISTS = 0x2C3,
		BD_AUTH_CREATE_USERNAME_ILLEGAL = 0x2C4,
		BD_AUTH_CREATE_USERNAME_VULGAR = 0x2C5,
		BD_AUTH_CREATE_MAX_ACC_EXCEEDED = 0x2C6,
		BD_AUTH_MIGRATE_NOT_SUPPORTED = 0x2C7,
		BD_AUTH_TITLE_DISABLED = 0x2C8,
		BD_AUTH_ACCOUNT_EXPIRED = 0x2C9,
		BD_AUTH_ACCOUNT_LOCKED = 0x2CA,
		BD_AUTH_UNKNOWN_ERROR = 0x2CB,
		BD_AUTH_INCORRECT_PASSWORD = 0x2CC,
		BD_AUTH_IP_NOT_IN_ALLOWED_RANGE = 0x2CD,
		BD_AUTH_WII_TOKEN_VERIFICATION_FAILED = 0x2CE,
		BD_AUTH_WII_AUTHENTICATION_FAILED = 0x2CF,
		BD_AUTH_IP_KEY_LIMIT_REACHED = 0x2D0,
		BD_AUTH_INVALID_GSPID = 0x2D1,
		BD_AUTH_INVALID_IP_RANGE_ID = 0x2D2,
		BD_AUTH_3DS_TOKEN_VERIFICATION_FAILED = 0x2D1,
		BD_AUTH_3DS_AUTHENTICATION_FAILED = 0x2D2,
		BD_AUTH_STEAM_APP_ID_MISMATCH = 0x2D3,
		BD_AUTH_ABACCOUNTS_APP_ID_MISMATCH = 0x2D4,
		BD_AUTH_CODO_USERNAME_NOT_SET = 0x2D5,
		BD_AUTH_WIIU_TOKEN_VERIFICATION_FAILED = 0x2D6,
		BD_AUTH_WIIU_AUTHENTICATION_FAILED = 0x2D7,
		BD_AUTH_CODO_USERNAME_NOT_BASE64 = 0x2D8,
		BD_AUTH_CODO_USERNAME_NOT_UTF8 = 0x2D9,
		BD_AUTH_TENCENT_TICKET_EXPIRED = 0x2DA,
		BD_AUTH_PS3_SERVICE_ID_MISMATCH = 0x2DB,
		BD_AUTH_CODOID_NOT_WHITELISTED = 0x2DC,
		BD_AUTH_PLATFORM_TOKEN_RETRIEVAL_ERROR = 0x2DD,
		BD_AUTH_JSON_FORMAT_ERROR = 0x2DE,
		BD_AUTH_REPLY_CONTENT_ERROR = 0x2DF,
		BD_AUTH_PLATFORM_TOKEN_EXPIRED = 0x2E0,
		BD_AUTH_CONTINUING = 0x2E1,
		BD_AUTH_PLATFORM_TOKEN_DECRYPTION_ERROR = 0x2E2,
		BD_AUTH_PLATFORM_TOKEN_SIGNATURE_ERROR = 0x2E3,
		BD_AUTH_DNS_RESOLUTION_ERROR = 0x2E4,
		BD_AUTH_SSL_CERTIFICATE_ERROR = 0x2E5,
		BD_AUTH_SERVER_UNAVAILABLE_ERROR = 0x2E6,
		BD_AUTH_ENVIRONMENT_ERROR = 0x2E7,
		BD_AUTH_PLATFORM_DEVICE_ID_ERROR = 0x2E8,
		BD_AUTH_UNO_APP_ID_MISMATCH = 0x2E9,
		BD_AUTH_UNICODE_DECODE_ERROR = 0x2EA,
		BD_AUTH_STEAM_PUBLISHER_BAN = 0x2EB,
		BD_AUTH_TICKET_DECRYPTION_ERROR = 0x2EC,
		BD_AUTH_SIGNATURE_ERROR = 0x2ED,
		BD_AUTH_SINGLE_IDENTITY_FLOW_DISABLED_ERROR = 0x2F0,
		BD_AUTH_SINGLE_IDENTITY_TOKEN_MISSING_ERROR = 0x2F1,
		BD_AUTH_SINGLE_IDENTITY_TOKEN_EXPIRED_ERROR = 0x2F2,
		BD_AUTH_SINGLE_IDENTITY_TOKEN_INVALID_ERROR = 0x2F3,
		BD_NO_PROFILE_INFO_EXISTS = 0x320,
		BD_FRIENDSHIP_NOT_REQUSTED = 0x384,
		BD_NOT_A_FRIEND = 0x385,
		BD_SELF_FRIENDSHIP_NOT_ALLOWED = 0x387,
		BD_FRIENDSHIP_EXISTS = 0x388,
		BD_PENDING_FRIENDSHIP_EXISTS = 0x389,
		BD_USERID_BANNED = 0x38A,
		BD_FRIENDS_FULL = 0x38C,
		BD_FRIENDS_NO_RICH_PRESENCE = 0x38D,
		BD_RICH_PRESENCE_TOO_LARGE = 0x38E,
		BD_NO_FILE = 0x3E8,
		BD_PERMISSION_DENIED = 0x3E9,
		BD_FILESIZE_LIMIT_EXCEEDED = 0x3EA,
		BD_FILENAME_MAX_LENGTH_EXCEEDED = 0x3EB,
		BD_EXTERNAL_STORAGE_SERVICE_ERROR = 0x3EC,
		BD_VALIDATION_ERROR = 0x3ED,
		BD_CHANNEL_DOES_NOT_EXIST = 0x44D,
		BD_CHANNEL_ALREADY_SUBSCRIBED = 0x44E,
		BD_CHANNEL_NOT_SUBSCRIBED = 0x44F,
		BD_CHANNEL_FULL = 0x450,
		BD_CHANNEL_SUBSCRIPTIONS_FULL = 0x451,
		BD_CHANNEL_NO_SELF_WHISPERING = 0x452,
		BD_CHANNEL_ADMIN_REQUIRED = 0x453,
		BD_CHANNEL_TARGET_NOT_SUBSCRIBED = 0x454,
		BD_CHANNEL_REQUIRES_PASSWORD = 0x455,
		BD_CHANNEL_TARGET_IS_SELF = 0x456,
		BD_CHANNEL_PUBLIC_BAN_NOT_ALLOWED = 0x457,
		BD_CHANNEL_USER_BANNED = 0x458,
		BD_CHANNEL_PUBLIC_PASSWORD_NOT_ALLOWED = 0x459,
		BD_CHANNEL_PUBLIC_KICK_NOT_ALLOWED = 0x45A,
		BD_CHANNEL_MUTED = 0x45B,
		BD_EVENT_DESC_TRUNCATED = 0x4B0,
		BD_CONTENT_UNLOCK_UNKNOWN_ERROR = 0x514,
		BD_UNLOCK_KEY_INVALID = 0x515,
		BD_UNLOCK_KEY_ALREADY_USED_UP = 0x516,
		BD_CONTENT_UNLOCK_LIMIT_REACHED = 0x517,
		BD_DIFFERENT_HARDWARE_ID = 0x518,
		BD_INVALID_CONTENT_OWNER = 0x519,
		BD_CONTENT_UNLOCK_INVALID_USER = 0x51A,
		BD_CONTENT_UNLOCK_INVALID_CATEGORY = 0x51B,
		BD_KEY_ARCHIVE_INVALID_WRITE_TYPE = 0x5DC,
		BD_KEY_ARCHIVE_EXCEEDED_MAX_IDS_PER_REQUEST = 0x5DD,
		BD_BANDWIDTH_TEST_TRY_AGAIN = 0x712,
		BD_BANDWIDTH_TEST_STILL_IN_PROGRESS = 0x713,
		BD_BANDWIDTH_TEST_NOT_PROGRESS = 0x714,
		BD_BANDWIDTH_TEST_SOCKET_ERROR = 0x715,
		BD_INVALID_SESSION_NONCE = 0x76D,
		BD_ARBITRATION_FAILURE = 0x76F,
		BD_ARBITRATION_USER_NOT_REGISTERED = 0x771,
		BD_ARBITRATION_NOT_CONFIGURED = 0x772,
		BD_CONTENTSTREAMING_FILE_NOT_AVAILABLE = 0x7D0,
		BD_CONTENTSTREAMING_STORAGE_SPACE_EXCEEDED = 0x7D1,
		BD_CONTENTSTREAMING_NUM_FILES_EXCEEDED = 0x7D2,
		BD_CONTENTSTREAMING_UPLOAD_BANDWIDTH_EXCEEDED = 0x7D3,
		BD_CONTENTSTREAMING_FILENAME_MAX_LENGTH_EXCEEDED = 0x7D4,
		BD_CONTENTSTREAMING_MAX_THUMB_DATA_SIZE_EXCEEDED = 0x7D5,
		BD_CONTENTSTREAMING_DOWNLOAD_BANDWIDTH_EXCEEDED = 0x7D6,
		BD_CONTENTSTREAMING_NOT_ENOUGH_DOWNLOAD_BUFFER_SPACE = 0x7D7,
		BD_CONTENTSTREAMING_SERVER_NOT_CONFIGURED = 0x7D8,
		BD_CONTENTSTREAMING_INVALID_APPLE_RECEIPT = 0x7DA,
		BD_CONTENTSTREAMING_APPLE_STORE_NOT_AVAILABLE = 0x7DB,
		BD_CONTENTSTREAMING_APPLE_RECEIPT_FILENAME_MISMATCH = 0x7DC,
		BD_CONTENTSTREAMING_BATCH_DOWNLOAD_PARTIAL_FAILURE = 0x7DD,
		BD_CONTENTSTREAMING_HTTP_ERROR = 0x7E4,
		BD_CONTENTSTREAMING_FAILED_TO_START_HTTP = 0x7E5,
		BD_CONTENTSTREAMING_LOCALE_INVALID = 0x7E6,
		BD_CONTENTSTREAMING_LOCALE_MISSING = 0x7E7,
		BD_VOTERANK_ERROR_EMPTY_RATING_SUBMISSION = 0x7EE,
		BD_VOTERANK_ERROR_MAX_VOTES_EXCEEDED = 0x7EF,
		BD_VOTERANK_ERROR_INVALID_RATING = 0x7F0,
		BD_MAX_NUM_TAGS_EXCEEDED = 0x82A,
		BD_TAGGED_COLLECTION_DOES_NOT_EXIST = 0x82B,
		BD_EMPTY_TAG_ARRAY = 0x82C,
		BD_SEARCH_SERVER_UNREACHABLE = 0x82F,
		BD_ENTITY_ID_NOT_SPECIFIED = 0x830,
		BD_INVALID_QUERY_ID = 0x834,
		BD_NO_ENTRY_TO_UPDATE = 0x835,
		BD_SESSION_INVITE_EXISTS = 0x836,
		BD_INVALID_SESSION_ID = 0x837,
		BD_ATTACHMENT_TOO_LARGE = 0x838,
		BD_INVALID_FIELD_VALUE = 0x839,
		BD_INVALID_GROUP_ID = 0xAF0,
		BD_MAIL_INVALID_MAIL_ID_ERROR = 0xB55,
		BD_MAIL_PERMISSION_DENIED_ERROR = 0xB56,
		BD_TWITCH_SERVICE_ERROR = 0xC1D,
		BD_TWITCH_ACCOUNT_ALREADY_LINKED = 0xC1E,
		BD_TWITCH_NO_LINKED_ACCOUNT = 0xC1F,
		BD_YOUTUBE_SERVICE_ERROR = 0xCE5,
		BD_YOUTUBE_SERVICE_COMMUNICATION_ERROR = 0xCE6,
		BD_YOUTUBE_USER_DENIED_AUTHORIZATION = 0xCE7,
		BD_YOUTUBE_AUTH_MAX_TIME_EXCEEDED = 0xCE8,
		BD_YOUTUBE_USER_UNAUTHORIZED = 0xCE9,
		BD_YOUTUBE_UPLOAD_MAX_TIME_EXCEEDED = 0xCEA,
		BD_YOUTUBE_DUPLICATE_UPLOAD = 0xCEB,
		BD_YOUTUBE_FAILED_UPLOAD = 0xCEC,
		BD_YOUTUBE_ACCOUNT_ALREADY_REGISTERED = 0xCED,
		BD_YOUTUBE_ACCOUNT_NOT_REGISTERED = 0xCEE,
		BD_YOUTUBE_CONTENT_SERVER_ERROR = 0xCEF,
		BD_YOUTUBE_UPLOAD_DOES_NOT_EXIST = 0xCF0,
		BD_YOUTUBE_NO_LINKED_ACCOUNT = 0xCF1,
		BD_YOUTUBE_DEVELOPER_TAGS_INVALID = 0xCF2,
		BD_TWITTER_AUTH_ATTEMPT_FAILED = 0xDAD,
		BD_TWITTER_AUTH_TOKEN_INVALID = 0xDAE,
		BD_TWITTER_UPDATE_LIMIT_REACHED = 0xDAF,
		BD_TWITTER_UNAVAILABLE = 0xDB0,
		BD_TWITTER_ERROR = 0xDB1,
		BD_TWITTER_TIMED_OUT = 0xDB2,
		BD_TWITTER_ACCOUNT_AMBIGUOUS = 0xDB4,
		BD_TWITTER_MAXIMUM_ACCOUNTS_REACHED = 0xDB5,
		BD_TWITTER_ACCOUNT_NOT_REGISTERED = 0xDB6,
		BD_TWITTER_DUPLICATE_STATUS = 0xDB7,
		BD_TWITTER_ACCOUNT_ALREADY_REGISTERED = 0xE1C,
		BD_FACEBOOK_AUTH_ATTEMPT_FAILED = 0xE11,
		BD_FACEBOOK_AUTH_TOKEN_INVALID = 0xE12,
		BD_FACEBOOK_PHOTO_DOES_NOT_EXIST = 0xE13,
		BD_FACEBOOK_PHOTO_INVALID = 0xE14,
		BD_FACEBOOK_PHOTO_ALBUM_FULL = 0xE15,
		BD_FACEBOOK_UNAVAILABLE = 0xE16,
		BD_FACEBOOK_ERROR = 0xE17,
		BD_FACEBOOK_TIMED_OUT = 0xE18,
		BD_FACEBOOK_DISABLED_FOR_USER = 0xE19,
		BD_FACEBOOK_ACCOUNT_AMBIGUOUS = 0xE1A,
		BD_FACEBOOK_MAXIMUM_ACCOUNTS_REACHED = 0xE1B,
		BD_FACEBOOK_INVALID_NUM_PICTURES_REQUESTED = 0xE1C,
		BD_FACEBOOK_VIDEO_DOES_NOT_EXIST = 0xE1D,
		BD_FACEBOOK_ACCOUNT_ALREADY_REGISTERED = 0xE1E,
		BD_FACEBOOK_TARGET_OBJECT_ID_INVALID = 0xE1F,
		BD_FACEBOOK_NO_SUCH_ACCOUNT = 0xE20,
		BD_APNS_INVALID_PAYLOAD = 0xE74,
		BD_APNS_INVALID_TOKEN_LENGTH_ERROR = 0xE76,
		BD_MAX_CONSOLEID_LENGTH_EXCEEDED = 0xEE1,
		BD_MAX_WHITELIST_LENGTH_EXCEEDED = 0xEE2,
		BD_TOTP_CHALLENGE_FAILED = 0xEE3,
		BD_NO_TOTP_ACCOUNT = 0xEE4,
		BD_EXTENDED_AUTH_INFO_ERROR = 0xEE5,
		BD_EXTENDED_AUTH_INFO_LENGTH_EXCEEDED = 0xEE6,
		BD_EXTENDED_AUTH_INFO_EXPIRED = 0xEE7,
		BD_WHITELIST_TRAILING_WHITE_SPACE = 0xEE8,
		BD_USERGROUP_NAME_ALREADY_EXISTS = 0x1770,
		BD_INVALID_USERGROUP_ID = 0x1771,
		BD_USER_ALREADY_IN_USERGROUP = 0x1772,
		BD_USER_NOT_IN_USERGROUP = 0x1773,
		BD_INVALID_USERGROUP_MEMBER_TYPE = 0x1774,
		BD_TOO_MANY_MEMBERS_REQUESTED = 0x1775,
		BD_USERGROUP_NAME_TOO_SHORT = 0x1776,
		BD_RICH_PRESENCE_DATA_TOO_LARGE = 0x1A90,
		BD_RICH_PRESENCE_TOO_MANY_USERS = 0x1A91,
		BD_PRESENCE_DATA_TOO_LARGE = 0x283C,
		BD_PRESENCE_TOO_MANY_USERS = 0x283D,
		BD_USER_LOGGED_IN_OTHER_TITLE = 0x283E,
		BD_USER_NOT_LOGGED_IN = 0x283F,
		BD_PRESENCE_INVALID_PLATFORM = 0x2840,
		BD_SUBSCRIPTION_TOO_MANY_USERS = 0x1B58,
		BD_SUBSCRIPTION_TICKET_PARSE_ERROR = 0x1B59,
		BD_CODO_ID_INVALID_DATA = 0x1BBC,
		BD_INVALID_MESSAGE_FORMAT = 0x1BBD,
		BD_TLOG_TOO_MANY_MESSAGES = 0x1BBE,
		BD_CODO_ID_NOT_IN_WHITELIST = 0x1BBF,
		BD_TLOG_MESSAGE_TRANSFORMATION_ERROR = 0x1BC0,
		BD_REWARDS_NOT_ENABLED = 0x1BC1,
		BD_REWARDS_INVALID_RULE = 0x1BC2,
		BD_REDEEM_NAME_CHANGE_INTERNAL_ERROR = 0x1BC3,
		BD_REDEEM_NAME_CHANGE_INVALID_ITEM = 0x1BC4,
		BD_REDEEM_NAME_CHANGE_UNAVAILABLE_ITEM = 0x1BC5,
		BD_REDEEM_NAME_CHANGE_IN_PROGRESS = 0x1BC6,
		BD_REDEEM_NAME_CHANGE_INACTIVE_REQUEST = 0x1BC7,
		BD_REDEEM_NAME_CHANGE_INVALID_NAME = 0x1BC8,
		BD_REDEEM_NAME_CHANGE_SAME_NAME = 0x1BC9,
		BD_REDEEM_NAME_CHANGE_DUPLICATE_NAME = 0x1BCA,
		BD_TENCENT_NO_APPLICABLE_REWARDS = 0x1BCB,
		BD_MARKETPLACE_ERROR = 0x1F40,
		BD_MARKETPLACE_RESOURCE_NOT_FOUND = 0x1F41,
		BD_MARKETPLACE_INVALID_CURRENCY = 0x1F42,
		BD_MARKETPLACE_INVALID_PARAMETER = 0x1F43,
		BD_MARKETPLACE_RESOURCE_CONFLICT = 0x1F44,
		BD_MARKETPLACE_STORAGE_ERROR = 0x1F45,
		BD_MARKETPLACE_INTEGRITY_ERROR = 0x1F46,
		BD_MARKETPLACE_INSUFFICIENT_FUNDS_ERROR = 0x1F47,
		BD_MARKETPLACE_MMP_SERVICE_ERROR = 0x1F48,
		BD_MARKETPLACE_PRECONDITION_REQUIRED = 0x1F49,
		BD_MARKETPLACE_ITEM_MULTIPLE_PURCHASE_ERROR = 0x1F4A,
		BD_MARKETPLACE_MISSING_REQUIRED_ENTITLEMENT = 0x1F4B,
		BD_MARKETPLACE_VALIDATION_ERROR = 0x1F4C,
		BD_MARKETPLACE_TENCENT_PAYMENT_ERROR = 0x1F4D,
		BD_MARKETPLACE_SKU_NOT_COUPON_ENABLED_ERROR = 0x1F4E,
		BD_MARKETPLACE_TRANSACTION_ERROR = 0x1F4F,
		BD_MARKETPLACE_RECEIPT_USED = 0x1F50,
		BD_MARKETPLACE_INVALID_RECEIPT = 0x1F51,
		BD_MARKETPLACE_STEAM_REQUEST_FAILED = 0x1F52,
		BD_MARKETPLACE_STEAM_NOT_APPROVED = 0x1F53,
		BD_MARKETPLACE_PRODUCT_NOT_FOUND_IN_FP = 0x1F54,
		BD_MARKETPLACE_STEAM_ALREADY_FINALIZED = 0x1F54,
		BD_MARKETPLACE_STEAM_BAD_ORDER_ID = 0x1F55,
		BD_MARKETPLACE_STEAM_CURRENCY_ERROR = 0x1F56,
		BD_MARKETPLACE_PSN_INVALID_NP_TITLE_ID = 0x1F65,
		BD_MARKETPLACE_PSN_INVALID_NP_AUTH_CODE = 0x1F57,
		BD_MARKETPLACE_PSN_INVALID_ENTITLEMENT_ID = 0x1F58,
		BD_MARKETPLACE_PSN_ENTITLEMENT_NOT_PRESENT = 0x1F59,
		BD_MARKETPLACE_PSN_INTERNAL_ERROR = 0x1F5A,
		BD_MARKETPLACE_XB1_UNAUTHORISED_ERROR = 0x1F5B,
		BD_MARKETPLACE_XB1_REQUEST_REJECTED_ERROR = 0x1F5C,
		BD_MARKETPLACE_XB1_INSUFFICIENT_QUANTITY_ERROR = 0x1F5D,
		BD_MARKETPLACE_XB1_BAD_DELEGATION_TOKEN_ERROR = 0x1F5E,
		BD_MARKETPLACE_XB1_REQUEST_FAILED_ERROR = 0x1F5F,
		BD_MARKETPLACE_X360_REQUEST_FAILED = 0x1F60,
		BD_MARKETPLACE_X360_ITEM_NOT_PRESENT = 0x1F61,
		BD_MARKETPLACE_X360_CONNECTION_ERROR = 0x1F62,
		BD_MARKETPLACE_USAGE_TIME_ERROR = 0x1F63,
		BD_MARKETPLACE_DURABLE_ALREADY_GRANTED = 0x1F64,
		BD_MARKETPLACE_FIRST_PARTY_DURABLE_EXISTS = 0x1F66,
		BD_MARKETPLACE_ITEM_LIMIT_REACHED = 0x1F67,
		BD_MARKETPLACE_OVER_ITEM_MAX_QUANTITY_ERROR = 0x1F69,
		BD_MARKETPLACE_INSUFFICIENT_ITEM_QUANTITY = 0x1F6A,
		BD_MARKETPLACE_ENTITY_NOT_ENABLED = 0x1F6B,
		BD_MARKETPLACE_MISCONFIGURED = 0x1F6C,
		BD_MARKETPLACE_COUPON_NOT_CLAIMED_OR_FOUND = 0x1F6D,
		BD_MARKETPLACE_INVALID_DISCOUNT = 0x1F6E,
		BD_MARKETPLACE_SKU_SOLD_OUT = 0x1F72,
		BD_MARKETPLACE_WIIU_AUTH_FAILED = 0x1F73,
		BD_MARKETPLACE_WIIU_INVALID_PARAMETER = 0x1F74,
		BD_MARKETPLACE_WIIU_TAX_LOCATION_NOT_SPECIFIED = 0x1F75,
		BD_MARKETPLACE_WIIU_ACCOUNT_ERROR = 0x1F76,
		BD_MARKETPLACE_WIIU_PURCHASING_ERROR = 0x1F77,
		BD_MARKETPLACE_WIIU_BALANCE_ERROR = 0x1F78,
		BD_MARKETPLACE_WIIU_SERVER_ERROR = 0x1F79,
		BD_MARKETPLACE_WIIU_REQUEST_FAILED = 0x1F7A,
		BD_MARKETPLACE_WIIU_SERVER_MAINTENANCE = 0x1F7B,
		BD_MARKETPLACE_WIIU_SERVICE_TERMINATED = 0x1F7C,
		BD_MARKETPLACE_WIIU_ITEM_NOT_PRESENT = 0x1F7D,
		BD_MARKETPLACE_WIIU_TAX_LOCATION_INVALID = 0x1F7E,
		BD_MARKETPLACE_XB1_DURABLE_NOT_PRESENT = 0x1F7F,
		BD_COMMS_SERVICE_NOT_AVAILABLE_ERROR = 0x28A0,
		BD_COMMS_CLIENT_ERROR = 0x28A1,
		BD_LEAGUE_INVALID_TEAM_SIZE = 0x1FA4,
		BD_LEAGUE_INVALID_TEAM = 0x1FA5,
		BD_LEAGUE_INVALID_SUBDIVISION = 0x1FA6,
		BD_LEAGUE_INVALID_LEAGUE = 0x1FA7,
		BD_LEAGUE_TOO_MANY_RESULTS_REQUESTED = 0x1FA8,
		BD_LEAGUE_METADATA_TOO_LARGE = 0x1FA9,
		BD_LEAGUE_TEAM_ICON_TOO_LARGE = 0x1FAA,
		BD_LEAGUE_TEAM_NAME_TOO_LONG = 0x1FAB,
		BD_LEAGUE_ARRAY_SIZE_MISMATCH = 0x1FAC,
		BD_LEAGUE_SUBDIVISION_MISMATCH = 0x2008,
		BD_LEAGUE_INVALID_WRITE_TYPE = 0x2009,
		BD_LEAGUE_INVALID_STATS_DATA = 0x200A,
		BD_LEAGUE_SUBDIVISION_UNRANKED = 0x200B,
		BD_LEAGUE_CROSS_TEAM_STATS_WRITE_PREVENTED = 0x200C,
		BD_LEAGUE_INVALID_STATS_SEASON = 0x200D,
		BD_COMMERCE_ERROR = 0x206C,
		BD_COMMERCE_RESOURCE_NOT_FOUND = 0x206D,
		BD_COMMERCE_STORAGE_INVALID_PARAMETER = 0x206E,
		BD_COMMERCE_APPLICATION_INVALID_PARAMETER = 0x206F,
		BD_COMMERCE_RESOURCE_CONFLICT = 0x2070,
		BD_COMMERCE_STORAGE_ERROR = 0x2071,
		BD_COMMERCE_INTEGRITY_ERROR = 0x2072,
		BD_COMMERCE_MMP_SERVICE_ERROR = 0x2073,
		BD_COMMERCE_PERMISSION_DENIED = 0x2074,
		BD_COMMERCE_INSUFFICIENT_FUNDS_ERROR = 0x2075,
		BD_COMMERCE_UNKNOWN_CURRENCY = 0x2076,
		BD_COMMERCE_INVALID_RECEIPT = 0x2077,
		BD_COMMERCE_RECEIPT_USED = 0x2078,
		BD_COMMERCE_TRANSACTION_ALREADY_APPLIED = 0x2079,
		BD_COMMERCE_INVALID_CURRENCY_TYPE = 0x207A,
		BD_COMMERCE_UNKNOWN_PLATFORM = 0x207B,
		BD_COMMERCE_WINDOWS_STORE_CERT_INVALID = 0x207C,
		BD_CONNECTION_COUNTER_ERROR = 0x20D0,
		BD_LINKED_ACCOUNTS_INVALID_CONTEXT = 0x2198,
		BD_LINKED_ACCOUNTS_INVALID_PLATFORM = 0x2199,
		BD_LINKED_ACCOUNTS_LINKED_ACCOUNTS_FETCH_ERROR = 0x219A,
		BD_LINKED_ACCOUNTS_INVALID_ACCOUNT = 0x219B,
		BD_LINKED_ACCOUNTS_INVALID_TOKEN = 0x219C,
		BD_QUEUED_MATCHING_ERROR = 0x2260,
		BD_QUEUED_MATCHING_NOT_FOUND = 0x2261,
		BD_QUEUED_MATCHING_WRONG_QUEUE_TYPE = 0x2262,
		BD_QUEUED_MATCHING_INVALID_QUEUE_ID = 0x2263,
		BD_LOGIN_QUEUE_NO_ERROR = 0x22C4,
		BD_LOGIN_QUEUE_ENVIRONMENT_ERROR = 0x22C5,
		BD_LOGIN_QUEUE_UNKNOWN_ERROR = 0x22C6,
		BD_LOGIN_QUEUE_BAD_REQUEST = 0x22C7,
		BD_LOGIN_QUEUE_SERVER_UNAVAILABLE_ERROR = 0x22C8,
		BD_LOGIN_QUEUE_SSL_CERTIFICATE_ERROR = 0x22C9,
		BD_LOGIN_QUEUE_DNS_RESOLUTION_ERROR = 0x22CA,
		BD_LOGIN_QUEUE_JSON_FORMAT_ERROR = 0x22CB,
		BD_LOGIN_QUEUE_TICKET_PARSE_ERROR = 0x22CC,
		BD_LOGIN_QUEUE_INVALID_TITLE_ID = 0x22CD,
		BD_VOTING_MAX_VALUE_EXCEEDED = 0x2328,
		BD_VOTING_INVALID_GROUP_NAME = 0x2329,
		BD_VOTING_IN_PROGRESS = 0x232A,
		BD_VOTING_NON_EXISTENT_GROUP = 0x232B,
		BD_USER_GENERATED_STATS_ERROR = 0x238C,
		BD_INVALID_ACCESS_TO_USER_GENERATED_LB_ERROR = 0x238D,
		BD_INVALID_ACCESS_TO_NON_USER_GENERATED_LB_ERROR = 0x238E,
		BD_SUB_LEADERBOARD_ID_MISMATCH_ERROR = 0x238D,
		BD_PUBLISHER_VARIABLES_SERVICE_ERROR = 0x251C,
		BD_PUBLISHER_VARIABLES_NOT_FOUND = 0x251D,
		BD_GMSG_INVALID_CATEGORY_ID = 0x27D8,
		BD_GMSG_CATEGORY_MEMBERSHIPS_LIMIT = 0x27D9,
		BD_GMSG_NONMEMBER_POST_DISALLOWED = 0x27DA,
		BD_GMSG_CATEGORY_DISALLOWS_CLIENT_TYPE = 0x27DB,
		BD_GMSG_PAYLOAD_TOO_BIG = 0x27DC,
		BD_GMSG_MEMBER_POST_DISALLOWED = 0x27DD,
		BD_GMSG_OVERLOADED = 0x27DE,
		BD_GMSG_USER_PERCATEGORY_POST_RATE_EXCEEDED = 0x27DF,
		BD_GMSG_USER_GLOBAL_POST_RATE_EXCEEDED = 0x27E0,
		BD_GMSG_GROUP_POST_RATE_EXCEEDED = 0x27E1,
		BD_CODO_CLAN_NO_TEMP_RESERVATION = 0x2AF8,
		BD_CODO_CLAN_TOO_MANY_MEMBERSHIPS = 0x2AF9,
		BD_CODO_CLAN_UNEXPECTED_FOUNDATION_STATE = 0x2AFA,
		BD_CODO_CLAN_UNABLE_TO_FIND_NAME = 0x2AFB,
		BD_CODO_CLAN_INTERNAL_MARKETPLACE_ERROR = 0x2AFC,
		BD_CODO_CLAN_INSUFFICIENT_FUNDS = 0x2AFD,
		BD_CODO_CLAN_UNSATISFIED_PRECONDITION = 0x2AFE,
		BD_CODO_CLAN_NO_CLAN = 0x2AFF,
		BD_CODO_CLAN_NO_CHANNEL = 0x2B00,
		BD_CODO_CLAN_NOT_A_CLAN_MEMBER = 0x2B01,
		BD_CODO_CLAN_DISBAND_TOO_MANY_MEMBERS = 0x2B04,
		BD_CODO_CLAN_DISBAND_TOO_SOON = 0x2B05,
		BD_NO_SUCH_ROLE = 0x2EE0,
		BD_NO_SUCH_PERMISSION = 0x2EE1,
		BD_BAD_ROLE_SPECIFICATION = 0x2EE2,
		BD_BAD_PERMISSION_SPECIFICATION = 0x2EE3,
		BD_REWARD_NO_REWARD_TOKEN_FOUND = 0x364C,
		BD_REWARD_INVALID_ACHIEVEMENT_IDS_SPECIFIED = 0x364D,
		BD_REWARD_CLIENT_ACHIEVEMENTS_NOT_ENABLED = 0x364E,
		BD_REWARD_EVENTS_ERROR = 0x364F,
		BD_REWARD_EVENTS_NOT_ENABLED = 0x3650,
		BD_REWARD_EVENTS_RULES_ERROR = 0x3651,
		BD_REWARD_EVENTS_DATA_ERROR = 0x3652,
		BD_REWARD_EVENTS_TRANSACTION_ERROR = 0x3653,
		BD_UMBRELLA_PROVIDER_SERVER_ERROR = 0x36B0,
		BD_UMBRELLA_PROVIDER_UNSUPPORTED_OPERATION = 0x36B1,
		BD_UMBRELLA_ERROR = 0x36B2,
		BD_UMBRELLA_INVALID_TITLE_ID = 0x36B3,
		BD_UMBRELLA_INVALID_QUERY_STRING = 0x36B4,
		BD_UMBRELLA_INVALID_DATA = 0x36B5,
		BD_UMBRELLA_INVALID_CLIENT = 0x36B6,
		BD_UMBRELLA_PROVIDER_NOT_SUPPORTED = 0x36B7,
		BD_UMBRELLA_UNAUTHORIZED_ACCESS = 0x36B8,
		BD_UMBRELLA_INVALID_TOKEN = 0x36B8,
		BD_UMBRELLA_EXPIRED_PROVIDER_REFRESH_TOKEN = 0x36B9,
		BD_UMBRELLA_NO_VALID_PROVIDER_TOKENS = 0x36BA,
		BD_UMBRELLA_INVALID_LSG_TICKET = 0x36BB,
		BD_UMBRELLA_TOKEN_NOT_FOUND = 0x36BC,
		BD_UMBRELLA_USER_NOT_FOUND = 0x36BD,
		BD_UMBRELLA_ACCOUNT_NOT_FOUND = 0x36BE,
		BD_UMBRELLA_MERGE_CONFLICT = 0x36BF,
		BD_UMBRELLA_PROVIDER_INACCESSIBLE = 0x36C0,
		BD_UMBRELLA_MISSING_FIELD = 0x36C1,
		BD_UNO_ERROR = 0x3714,
		BD_UNO_INVALID_DATA = 0x3715,
		BD_UNO_INVALID_DATE_OF_BIRTH = 0x3716,
		BD_UNO_UNAUTHORIZED_ACCESS = 0x3717,
		BD_UNO_INVALID_TOKEN = 0x3718,
		BD_UNO_EXPIRED_TOKEN = 0x3719,
		BD_UNO_EMAIL_NOT_VERIFIED = 0x371A,
		BD_UNO_TOS_VERSION_NOT_FOUND = 0x371B,
		BD_UNO_TOS_CONTENT_NOT_FOUND = 0x371C,
		BD_UNO_TOS_ALREADY_ACCEPTED = 0x371D,
		BD_UNO_MISSING_FIELD = 0x371E,
		BD_UNO_DNS_RESOLUTION_FAILED = 0x371F,
		BD_SI_ERROR = 0x3777,
		BD_MAX_ERROR_CODE = 0x3778,
	};

	enum LobbyModule
	{
		LOBBY_MODULE_INVALID = 0xFFFFFFFF,
		LOBBY_MODULE_HOST = 0x0,
		LOBBY_MODULE_CLIENT = 0x1,
		LOBBY_MODULE_COUNT = 0x2,
		LOBBY_MODULE_FIRST = 0x0,
		LOBBY_MODULE_LAST = 0x1,
		LOBBY_MODULE_PEER_TO_PEER = 0x3,
	};

    // Sepatrate Enums & Structures;

    union netipv4_t
    {
        std::uint8_t octets[4];
        std::uint32_t inaddr;
    };

#pragma pack(push, 1)
    struct XNADDR
    {
        union addrbuff_u
        {
            struct addrbuff_s
            {
            private:
                byte _0x0[0x1E];
            public:
                netipv4_t ipv4;
                std::uint16_t port;
            private:
                byte _0x24[0x1];
            } ab;

            std::uint8_t bytes[37];
        } addrBuff;
    };
#pragma pack(pop)

    struct SerializedAdr
    {
    public:
        bool valid;
        XNADDR xnaddr;
    };

    struct netadr_t
    {
    public:
        netipv4_t ipv4;
        std::uint16_t port;
        netadrtype_t type;
        netsrc_t localNetID;
    };

    struct MatchMakingQuery
    {
        char pad[0x10];
        QueryId queryId;
        uint64_t securityID;
        int showInMatchmaking;
        int netcodeVersion;
        int mapPacks;
        int playlistVersion;
        int playlistNum;
        int serverType;
        int isEmpty;
        int teamSize;
        char pad2[0x78];
    };

    struct bdSecurityID
    {
        std::uint64_t id;
    };

    struct bdMatchMakingInfo
    {
        bdSecurityID sessionID;
        uint8_t hostAddr[255];
        uint32_t hostAddrSize;
        uint32_t gameType;
        uint32_t maxPlayers;
        uint32_t numPlayers;
    };

    struct bdSecurityKey
    {
    public:
        std::uint8_t ab[16];
    }; typedef bdSecurityKey XNKEY;

    struct HostInfo
    {
        uint64_t xuid;
        char name[32];
        netadr_t netAdr;
        SerializedAdr serializedAdr;
        bdSecurityID secId;
        bdSecurityKey secKey;
        uint32_t serverLocation;
    };

    struct MatchMakingInfo
    {
        char pad[0x20];
        bdMatchMakingInfo info;
        uint64_t sessionID;
        char keyExchangeKey[17];
        int serverType;
        uint64_t xuid;
        uint32_t serverLocation;
        uint32_t latencyBand;
        int showInMatchmaking;
        int netcodeVersion;
        int mapPacks;
        int playlistVersion;
        int playlistNumber;
        int isEmpty;
        int teamMax;
        float skill;
        int geo1;
        int geo2;
        int geo3;
        int geo4;
        int dirty;
        int active;
        int timeSinceLastUpdate;
        int recreateSession;
        int timeSinceUpdate;
        char pad2[0x14];

        HostInfo get_host_info() const
        {
            HostInfo host_info{};
            host_info.xuid = xuid;
            host_info.secId.id = sessionID;
            host_info.secKey = *reinterpret_cast<const bdSecurityKey*>(keyExchangeKey);
            host_info.serializedAdr.xnaddr = *reinterpret_cast<const XNADDR*>(info.hostAddr);
            return host_info;
        }

        bool operator<(const MatchMakingInfo& other) const
        {
            return info.numPlayers > other.info.numPlayers;
        }
    };

    struct TaskRecord;
    using task_callback = void(*)(TaskRecord*);

    struct TaskDefinition
    {
        const uint64_t category;
        const char* const name;
        const int payloadSize;
        const task_callback completed_callback;
        const task_callback failure_callback;
    };

    struct bdRemoteTask
    {
        char pad[0x38];
        uint32_t numResults;
        uint32_t maxNumResults;
        uint32_t totalNumResults;
        uint64_t transactionID;
        bdLobbyErrorCode errorCode;
        void* taskResultProcessor;
        uint8_t serviceId;
        uint8_t taskId;
    };

    struct TaskRecord
    {
        TaskRecord* next;
        const TaskDefinition* definition;
        TaskState state;
        unsigned int controllerIndex;
        unsigned int lastPoll;
        unsigned int lastPollMS;
        unsigned int id;
        int startMS;
        int timeOut;
        int timeIn;
        char pad[0x8];
        bdRemoteTask* remoteTask;
        TaskRecord* nestedTask;
        void* payload;
    };
}

namespace offsets
{
    const static auto sub_0xDF4D69BF = Engine::offset(0xDF4D69BF);
	const static auto sub_0xDF4D694F = Engine::offset(0xDF4D694F);
    const static auto sub_0xDF402A3F = Engine::offset(0xDF402A3F);
    const static auto sub_0xDF43FBEF = Engine::offset(0xDF43FBEF);
    const static auto sub_0xDF43E36F = Engine::offset(0xDF43E36F);
	const static auto sub_0xDC8743FF = Engine::offset(0xDC8743FF);
	const static auto sub_0xDC86B28F = Engine::offset(0xDC86B28F);
	const static auto sub_0xDC87455F = Engine::offset(0xDC87455F);
	const static auto sub_0xDC86B3CF = Engine::offset(0xDC86B3CF);
	const static auto sub_0xDC86B63F = Engine::offset(0xDC86B63F);
	const static auto sub_0xDFE90C3F = Engine::offset(0xDFE90C3F);
	const static auto sub_0xDC698243 = Engine::offset(0xDC698243);
	const static auto sub_0xDC3D181F = Engine::offset(0xDC3D181F);
	const static auto sub_0xDFE96C0F = Engine::offset(0xDFE96C0F);
	const static auto sub_0xDFEE7D8F = Engine::offset(0xDFEE7D8F);
	const static auto sub_0xDF410C5F = Engine::offset(0xDF410C5F);
	const static auto sub_0xDF417CAF = Engine::offset(0xDF417CAF);
	const static auto sub_0xDF402FFF = Engine::offset(0xDF402FFF);
	const static auto sub_0xDF417F9F = Engine::offset(0xDF417F9F);
}

namespace functions
{
    static bool sub_0xDF4D69BF(structures::Enum1 param1)
    {
        using Func_type = bool(__fastcall*)(structures::Enum1);
        auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDF4D69BF);

        return func_ptr(param1);
    }

	static bool sub_0xDF4D694F(structures::Enum1 param1)
	{
		using Func_type = bool(__fastcall*)(structures::Enum1);
		auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDF4D694F);

		return func_ptr(param1);
	}

    static bool sub_0xDF402A3F(int param1, int param2, structures::LobbyType param3, structures::LobbyType param4)
    {
        using Func_type = bool(__fastcall*)(int, int, structures::LobbyType, structures::LobbyType);
        auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDF402A3F);

        return func_ptr(param1, param2, param3, param4);
    }

    static bool sub_0xDF43FBEF(uint64_t param1, const char* param2, const structures::bdSecurityID* param3, const structures::bdSecurityKey* param4, const structures::SerializedAdr* param5, structures::JoinType param6, uint64_t param7)
    {
        using Func_type = bool(__fastcall*)(uint64_t, const char*, const structures::bdSecurityID*, const structures::bdSecurityKey*, const structures::SerializedAdr*, structures::JoinType, uint64_t);
        auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDF43FBEF);

        return func_ptr(param1, param2, param3, param4, param5, param6, param7);
    }

    static bool sub_0xDF43E36F()
    {
        using Func_type = bool(*)();
        auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDF43E36F);

        return func_ptr();
    }

	static structures::TaskRecord* sub_0xDC8743FF(const void* param1, structures::Enum1 param2, structures::TaskRecord* param3, int param4)
	{
		using Func_type = structures::TaskRecord * (__fastcall*)(const void*, structures::Enum1, structures::TaskRecord*, int);
		auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDC8743FF);

		return func_ptr(param1, param2, param3, param4);
	}

	static void sub_0xDC86B28F(structures::TaskRecord* param1)
	{
		using Func_type = void(__fastcall*)(structures::TaskRecord*);
		auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDC86B28F);

		func_ptr(param1);
	}

	static void sub_0xDC87455F(const void* param1)
	{
		using Func_type = void(__fastcall*)(const void*);
		auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDC87455F);

		func_ptr(param1);
	}

	static bool sub_0xDC86B3CF(const void* param1)
	{
		using Func_type = bool(__fastcall*)(const void*);
		auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDC86B3CF);

		return func_ptr(param1);
	}

	static void sub_0xDC86B63F(structures::TaskRecord* param1)
	{
		using Func_type = void(__fastcall*)(structures::TaskRecord*);
		auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDC86B63F);

		func_ptr(param1);
	}

	static uintptr_t sub_0xDFE90C3F(int param1)
	{
		using Func_type = uintptr_t(*)(int);
		auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDFE90C3F);

		return func_ptr(param1);
	}

	static void sub_0xDC698243(void* param1, unsigned long long param2, size_t param3, uintptr_t param4, uintptr_t param5)
	{
		using Func_type = void(__fastcall*)(void*, unsigned long long, size_t, uintptr_t, uintptr_t);
		auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDC698243);

		func_ptr(param1, param2, param3, param4, param5);
	}

	static structures::bdRemoteTask* sub_0xDC3D181F(const uintptr_t param1, structures::bdRemoteTask** param2, structures::QueryId param3, int param4, size_t param5, structures::MatchMakingQuery* param6, structures::MatchMakingInfo* param7)
	{
		using Func_type = structures::bdRemoteTask * (__fastcall*)(const uintptr_t, structures::bdRemoteTask**, structures::QueryId, int, size_t, structures::MatchMakingQuery*, structures::MatchMakingInfo*);
		auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDC3D181F);

		return func_ptr(param1, param2, param3, param4, param5, param6, param7);
	}

	static uintptr_t sub_0xDFE96C0F(structures::MatchMakingQuery* param1, int param2, bool param3)
	{
		using Func_type = uintptr_t(__fastcall*)(structures::MatchMakingQuery*, int, bool);
		auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDFE96C0F);

		return func_ptr(param1, param2, param3);
	}

	static bool sub_0xDFEE7D8F(structures::netadr_t* const param1, const void* const param2, const structures::bdSecurityID* param3)
	{
		using Func_type = bool(__fastcall*)(structures::netadr_t* const, const void* const, const structures::bdSecurityID*);
		auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDFEE7D8F);

		return func_ptr(param1, param2, param3);
	}

	static char* sub_0xDF410C5F(unsigned int param1)
	{
		using Func_type = char* (__fastcall*)(unsigned int param1);
		auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDF410C5F);

		return func_ptr(param1);
	}

	static bool sub_0xDF417CAF(structures::LobbyType param1)
	{
		using Func_type = bool(__fastcall*)(structures::LobbyType);
		auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDF417CAF);

		return func_ptr(param1);
	}

	static bool sub_0xDF402FFF(structures::LobbyType param1)
	{
		using Func_type = bool(__fastcall*)(structures::LobbyType);
		auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDF402FFF);

		return func_ptr(param1);
	}

	static bool sub_0xDF417F9F(structures::LobbyModule param1)
	{
		using Func_type = bool(__fastcall*)(structures::LobbyModule);
		auto func_ptr = reinterpret_cast<Func_type>(offsets::sub_0xDF417F9F);

		return func_ptr(param1);
	}
}

namespace selfmade_functions
{
	static void function_one(const structures::HostInfo& param1)
	{
		const bool part_one = functions::sub_0xDF402A3F(0, 0, structures::LOBBY_TYPE_PRIVATE, structures::LOBBY_TYPE_GAME);

		if (!part_one)
			return;

		const bool part_two = functions::sub_0xDF43FBEF(param1.xuid, param1.name, &param1.secId, &param1.secKey, &param1.serializedAdr, structures::JOIN_TYPE_NORMAL, param1.xuid);

		if (!part_two)
			return;

		functions::sub_0xDF43E36F();
	}

	static long long function_two(unsigned int param1)
	{
		char* part_one = functions::sub_0xDF410C5F(param1);

		long long part_two = *reinterpret_cast<long long*>(part_one);

		return part_two;
	}

	static bool function_three(structures::LobbyModule param1, structures::LobbyType param2)
	{
		if (param1)
			return functions::sub_0xDF417CAF(param2);

		else
			return functions::sub_0xDF402FFF(param2);
	}
}

namespace string
{
	static std::string va(const char* format, ...)
	{
		va_list args;
		va_start(args, format);

		int size = std::vsnprintf(nullptr, 0, format, args) + 1;
		va_end(args);

		char* buffer = new char[size];
		va_start(args, format);
		std::vsnprintf(buffer, size, format, args);
		va_end(args);

		std::string result(buffer);
		delete[] buffer;

		return result;
	}
}

namespace helper
{
	static std::string XNADDR_to_string(const structures::XNADDR* xnaddr)
	{
		return string::va
		(
			"%u.%u.%u.%u:%u",
			xnaddr->addrBuff.ab.ipv4.octets[0],
			xnaddr->addrBuff.ab.ipv4.octets[1],
			xnaddr->addrBuff.ab.ipv4.octets[2],
			xnaddr->addrBuff.ab.ipv4.octets[3],
			xnaddr->addrBuff.ab.port
		);
	}

	static structures::LobbyModule get_current_lobby_module()
	{
		return structures::LOBBY_MODULE_CLIENT;
	}

	static structures::LobbyType get_current_lobby_type()
	{
		if (functions::sub_0xDF417F9F(structures::LOBBY_MODULE_CLIENT))
		{
			return structures::LOBBY_TYPE_GAME;
		}

		else
		{
			return structures::LOBBY_TYPE_PRIVATE;
		}
	}

	static bool are_we_host()
	{
		return selfmade_functions::function_three(get_current_lobby_module(), get_current_lobby_type());
	}
}

#endif //ENGINE_H
