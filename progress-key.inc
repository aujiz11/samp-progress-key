// created by Ausil (#aujiz)

#if defined _inc_progress_key_
    #endinput
#endif
#define _inc_progress_key_

#tryinclude <YSI_Data\y_bit>
#tryinclude <YSI_Coding\y_va>

#if !defined _INC_open_mp
    #tryinclude <YSF>

    #if !defined _YSF_included
        #error The YSF plugin is required
    #endif

	#if !defined TEXT_DRAW_ALIGN
		#define TEXT_DRAW_ALIGN: _:
	#endif

	#if !defined TEXT_DRAW_FONT
		#define TEXT_DRAW_FONT: _:
	#endif

    #if !defined KEY
        #define KEY: _:
    #endif
#endif

#define Progress_Key(%0) \
            (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

// Progress:%0(playerid, success)
#define Progress:%0(%1) \
            forward prog_%0(%1); public prog_%0(%1)

#define Progress_Show(%0,%1,%2, \
            Progress_Start(%0,%1,#%2,

const Float:MIN_PROGRESS_POS = 300.0;
const Float:MAX_PROGRESS_POS = 365.0;
const Float:MAX_TEXT_SIZE = 132.0;

static Float:a_ProgressRenderPos[MAX_PLAYERS] = {MIN_PROGRESS_POS, ...};
static a_ProgressInterval[MAX_PLAYERS];

#if defined _INC_y_bit
    static BitArray: a_ProgressOpen <MAX_PLAYERS>;
#else
    static bool: a_ProgressOpen[MAX_PLAYERS];
#endif

static a_ProgressFunction[MAX_PLAYERS][36];

static Text: txd_ProgressGlobal[3];
static PlayerText: txd_ProgressPlayer[MAX_PLAYERS][3];

stock Progress_Valid(playerid)  
{
    #if defined _INC_y_bit
        return Bit_Get(a_ProgressOpen, playerid);
    #else
        return a_ProgressOpen[playerid];
    #endif
}

static bool:Progress_Render(playerid, const message[], Float:textX)
{
    txd_ProgressPlayer[playerid][0] = CreatePlayerTextDraw(playerid, 255.000, 284.000, message);
    PlayerTextDrawLetterSize(playerid, txd_ProgressPlayer[playerid][0], 0.180, 1.399);
    PlayerTextDrawAlignment(playerid, txd_ProgressPlayer[playerid][0], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, txd_ProgressPlayer[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, txd_ProgressPlayer[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, txd_ProgressPlayer[playerid][0], 0);
    PlayerTextDrawBackgroundColour(playerid, txd_ProgressPlayer[playerid][0], 150);
    PlayerTextDrawFont(playerid, txd_ProgressPlayer[playerid][0], TEXT_DRAW_FONT_2);
    PlayerTextDrawSetProportional(playerid, txd_ProgressPlayer[playerid][0], true);
    PlayerTextDrawShow(playerid, txd_ProgressPlayer[playerid][0]);

    txd_ProgressPlayer[playerid][1] = CreatePlayerTextDraw(playerid, textX, 301.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, txd_ProgressPlayer[playerid][1], 11.000, 18.000);
    PlayerTextDrawAlignment(playerid, txd_ProgressPlayer[playerid][1], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, txd_ProgressPlayer[playerid][1], -708759297);
    PlayerTextDrawSetShadow(playerid, txd_ProgressPlayer[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, txd_ProgressPlayer[playerid][1], 0);
    PlayerTextDrawBackgroundColour(playerid, txd_ProgressPlayer[playerid][1], 255);
    PlayerTextDrawFont(playerid, txd_ProgressPlayer[playerid][1], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, txd_ProgressPlayer[playerid][1], true);
    PlayerTextDrawShow(playerid, txd_ProgressPlayer[playerid][1]);

    txd_ProgressPlayer[playerid][2] = CreatePlayerTextDraw(playerid, 254.000, 301.000, "LD_SPAC:white"); // Progress Bar
    PlayerTextDrawTextSize(playerid, txd_ProgressPlayer[playerid][2], 0.000, 18.000);
    PlayerTextDrawAlignment(playerid, txd_ProgressPlayer[playerid][2], TEXT_DRAW_ALIGN_LEFT);
    PlayerTextDrawColour(playerid, txd_ProgressPlayer[playerid][2], 866792447);
    PlayerTextDrawSetShadow(playerid, txd_ProgressPlayer[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, txd_ProgressPlayer[playerid][2], 0);
    PlayerTextDrawBackgroundColour(playerid, txd_ProgressPlayer[playerid][2], 255);
    PlayerTextDrawFont(playerid, txd_ProgressPlayer[playerid][2], TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawSetProportional(playerid, txd_ProgressPlayer[playerid][2], true);
    PlayerTextDrawShow(playerid, txd_ProgressPlayer[playerid][2]);

    return true;
}

static bool:Progress_Reset(playerid)
{
    for(new i;i<3;i++) {
        TextDrawHideForPlayer(playerid, txd_ProgressGlobal[i]);
        PlayerTextDrawDestroy(playerid, txd_ProgressPlayer[playerid][i]);
        txd_ProgressPlayer[playerid][i] = INVALID_PLAYER_TEXT_DRAW;
    }

    #if defined _INC_y_bit
        Bit_Vet(a_ProgressOpen, playerid);
    #else
        a_ProgressOpen[playerid] = false;
    #endif

    a_ProgressFunction[playerid][0] = EOS;
    a_ProgressRenderPos[playerid] = MIN_PROGRESS_POS;
    a_ProgressInterval[playerid] = 0;
    return true;
}

#if defined _INC_y_va
    stock bool:Progress_Start(playerid, interval, const function[], const message[], va_args<>) 
#else
    stock bool:Progress_Start(playerid, interval, const function[], const message[]) 
#endif
{

    if (Progress_Valid(playerid))
        return false;

    if (!IsPlayerConnected(playerid))
        return false;

    TextDrawShowForPlayer(playerid, txd_ProgressGlobal[0]);
    TextDrawShowForPlayer(playerid, txd_ProgressGlobal[1]);
    TextDrawShowForPlayer(playerid, txd_ProgressGlobal[2]);

    new Float:progress_rand = RandomFloatMinMax(MIN_PROGRESS_POS, MAX_PROGRESS_POS);

    #if defined _INC_y_va
        new str[256];
        va_format(str, sizeof(str), message, va_start<4>);
        Progress_Render(playerid, str, progress_rand);
    #else
        Progress_Render(playerid, message, progress_rand);
    #endif

    #if defined _INC_y_bit
        Bit_Let(a_ProgressOpen, playerid);
    #else
        a_ProgressOpen[playerid] = true;
    #endif

    a_ProgressRenderPos[playerid] = progress_rand;
    a_ProgressInterval[playerid] = interval;
    strunpack(a_ProgressFunction[playerid], function);

    SetTimerEx("Progress_TimerG", interval, false, "d", playerid);
    return true;
}

forward Progress_TimerG(playerid);
public Progress_TimerG(playerid)
{
    if (!Progress_Valid(playerid))
        return 0;

    if (!IsPlayerConnected(playerid))
        return 0;

    new Float:width, Float:height, func_call[36];
    
    PlayerTextDrawGetTextSize(playerid, txd_ProgressPlayer[playerid][2], width, height);
    if (0.0 <= width < MAX_TEXT_SIZE)
    {
        PlayerTextDrawTextSize(playerid, txd_ProgressPlayer[playerid][2], width + 0.5, height);
        PlayerTextDrawShow(playerid, txd_ProgressPlayer[playerid][2]);

        SetTimerEx("Progress_TimerG", a_ProgressInterval[playerid], false, "d", playerid);
        return 1;
    }
    
    format(func_call, _, "prog_%s", a_ProgressFunction[playerid]);
    CallRemoteFunction(func_call, "dd", playerid, 0);

    Progress_Reset(playerid);
    return 1;
}

public OnGameModeInit()
{
    txd_ProgressGlobal[0] = TextDrawCreate(252.000, 281.000, "LD_SPAC:white");
    TextDrawTextSize(txd_ProgressGlobal[0], 136.000, 41.000);
    TextDrawAlignment(txd_ProgressGlobal[0], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColour(txd_ProgressGlobal[0], 421075455);
    TextDrawSetShadow(txd_ProgressGlobal[0], 0);
    TextDrawSetOutline(txd_ProgressGlobal[0], 0);
    TextDrawBackgroundColour(txd_ProgressGlobal[0], 255);
    TextDrawFont(txd_ProgressGlobal[0], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawSetProportional(txd_ProgressGlobal[0], true);

    txd_ProgressGlobal[1] = TextDrawCreate(254.000, 301.000, "LD_SPAC:white");
    TextDrawTextSize(txd_ProgressGlobal[1], 132.000, 18.000);
    TextDrawAlignment(txd_ProgressGlobal[1], TEXT_DRAW_ALIGN_LEFT);
    TextDrawColour(txd_ProgressGlobal[1], 1130382335);
    TextDrawSetShadow(txd_ProgressGlobal[1], 0);
    TextDrawSetOutline(txd_ProgressGlobal[1], 0);
    TextDrawBackgroundColour(txd_ProgressGlobal[1], 255);
    TextDrawFont(txd_ProgressGlobal[1], TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawSetProportional(txd_ProgressGlobal[1], true);

    txd_ProgressGlobal[2] = TextDrawCreate(292.000, 305.000, "PRESS (H) ON THE BAR TO PROCEED");
    TextDrawLetterSize(txd_ProgressGlobal[2], 0.119, 0.999);
    TextDrawAlignment(txd_ProgressGlobal[2], TEXT_DRAW_ALIGN_CENTER);
    TextDrawColour(txd_ProgressGlobal[2], -1);
    TextDrawSetShadow(txd_ProgressGlobal[2], 0);
    TextDrawSetOutline(txd_ProgressGlobal[2], 0);
    TextDrawBackgroundColour(txd_ProgressGlobal[2], 150);
    TextDrawFont(txd_ProgressGlobal[2], TEXT_DRAW_FONT_2);
    TextDrawSetProportional(txd_ProgressGlobal[2], true);

	#if defined AP_OnGameModeInit
		return AP_OnGameModeInit();
	#else
		return 1;
	#endif
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif

#define OnGameModeInit AP_OnGameModeInit

#if defined AP_OnGameModeInit
	forward AP_OnGameModeInit();
#endif

public OnPlayerConnect(playerid)
{
    a_ProgressRenderPos[playerid] = MIN_PROGRESS_POS;
    a_ProgressFunction[playerid][0] = EOS;
    a_ProgressInterval[playerid] = 0;

    #if defined _INC_y_bit
        Bit_Vet(a_ProgressOpen, playerid);
    #else
        a_ProgressOpen[playerid] = false;
    #endif

	#if defined AP_OnPlayerConnect
		return AP_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect AP_OnPlayerConnect
#if defined AP_OnPlayerConnect
	forward AP_OnPlayerConnect(playerid);
#endif

public OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys)
{
    if (Progress_Key(KEY:2) || Progress_Key(KEY_CTRL_BACK))
    {
        if (Progress_Valid(playerid) && a_ProgressFunction[playerid][0] != EOS)
        {
            new 
                Float:width, Float:height, 
                Float:press_range = 47.0 + (a_ProgressRenderPos[playerid] - MIN_PROGRESS_POS); // phạm vi nhỏ nhất để nhấn

            new func_call[36];
            format(func_call, _, "prog_%s", a_ProgressFunction[playerid]);

            PlayerTextDrawGetTextSize(playerid, txd_ProgressPlayer[playerid][2], width, height);
            
            if (press_range <= width <= (press_range + 10.0)) // phạm vi có thể nhấn trong khoảng 10.0
                CallRemoteFunction(func_call, "dd", playerid, 1);
            else 
                CallRemoteFunction(func_call, "dd", playerid, 0);

            Progress_Reset(playerid);
        }
    }

	#if defined AP_OnPlayerKeyStateChange
		return AP_OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif

#define OnPlayerKeyStateChange AP_OnPlayerKeyStateChange
#if defined AP_OnPlayerKeyStateChange
	forward AP_OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys);
#endif