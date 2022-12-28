/* See LICENSE file for copyright and license details. */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "firefox"
#define BROWSERCLASS "firefox"


/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */

static unsigned int gappih   		= 0;       /* horiz inner gap between windows */
static unsigned int gappiv    		= 0;       /* vert inner gap between windows */
static unsigned int gappoh    		= 0;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    		= 0;       /* vert outer gap between windows and screen edge */
static int smartgaps                = 0;        /* 1 means no outer gap when there is only one window */
static int showbar            		= 1;        /* 0 means no bar */
static int topbar             		= 1;        /* 0 means bottom bar */
static const char *fonts[] = {"Terminus:pixelsize=17"};
static const char dmenufont[] = {"Terminus:pixelsize=17"};
static const char normfgcolor[]           = "#bbbbbb";
static const char normbgcolor[]           = "#222222";
static const char normbordercolor[]       = "#444444";
static const char selfgcolor[]            = "#eeeeee";
static const char selbgcolor[]            = "#005577";
static const char selbordercolor[]        = "#005577";
static const char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
    [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
    const char *name;
    const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "100x30", NULL };
static Sp scratchpads[] = {
    /* name          cmd  */
    {"spterm",      spcmd1},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9"};
static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
    */
    /* class                    instance  title           tags mask  isfloating  monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {BROWSERCLASS, NULL, NULL, 1 << 8, 0, -1},
    {"Chromium", NULL, NULL, 1 << 8, 0, -1},
    {"qBittorrent", NULL, NULL, 1 << 7, 0, -1},
    {NULL, NULL, "Event Tester", 0, 1, -1}, /* xev */
    /* {"Sxiv", NULL, NULL, 0, 1, -1}, */
    {"Dragon", NULL, NULL, ~0, 1, -1},
    {NULL, NULL, "Picture-in-picture", ~0, 1, -1},
    {"VSCodium", NULL, NULL, 1 << 4, 0, -1},
    {"code-oss", NULL, NULL, 1 << 4, 0, -1},
    /* {"Emacs", NULL, NULL, 1 << 2, 0, -1}, */
    {"jetbrains-idea-ce", NULL, NULL, 1 << 3, 0, -1},
    {"java-util-concurrent-ForkJoinWorkerThread", NULL, NULL, 1 << 3, 0, -1},
    /* {NULL, NULL, "Eclipse", 1 << 3, 0, -1}, */
    {NULL, NULL, "LibreOffice", 1 << 6, 0, -1},
    {"Gimp", NULL, NULL, 1 << 5, 0, -1},
    {"TelegramDesktop", NULL, NULL, 1 << 4, 0, -1},
    { NULL,		 "spterm",		NULL,	    	SPTAG(0), 1,    	-1 },
    /* { NULL,		 "spcalc",      	NULL,		SPTAG(1), 1,    	-1 }, */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "[D]",      deck },
    { "[@]",      spiral },
    /* { "TTT",      bstack }, */
    /* { "|M|",      centeredmaster }, */
    { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)																								\
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
        { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#include <X11/XF86keysym.h>
#include "shiftview.c"



/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };
static char dmenumon[2] = "0"; /* 1component of dmenucmd, manipulated in spawn() *1/ */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };


#include "movestack.c"
static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,               			XK_p,       spawn,          {.v = dmenucmd } },
    {MODKEY | ShiftMask, XK_d, spawn, {.v = (const char *[]){"dmenuhandlerXclip", NULL}}},
    {MODKEY | ShiftMask, XK_p, spawn, {.v = (const char *[]){"passmenu", NULL}}},
    {MODKEY, XK_v, spawn, {.v = (const char *[]){"clipmenu", "-i", "-l", "15", NULL}}},
    {MODKEY | ShiftMask, XK_v, spawn, {.v = (const char *[]){TERMINAL, "-e", "pulsemixer", NULL}}},
    {MODKEY, XK_grave, spawn, {.v = (const char *[]){"dmenuunicode", "-i", NULL}}},
    {MODKEY, XK_i, spawn, {.v = (const char *[]){TERMINAL, "-e","my-tmux-session", NULL}}},
    {MODKEY|ShiftMask, XK_i, spawn, {.v = (const char *[]){"emacs", NULL}}},
    {MODKEY | Mod1Mask, XK_slash, spawn, {.v = (const char *[]){TERMINAL, "-e", "transs", NULL}}},
    // {Mod1Mask, XK_space, spawn, //  SHCMD(" xkb-switch --next; pkill -RTMIN+21 dwmblocks ;")},
    {MODKEY, XK_slash, spawn, {.v = (const char *[]){"transXclip", NULL}}},
    {MODKEY | ShiftMask, XK_slash, spawn, {.v = (const char *[]){"transXcclip", NULL}}},
    {MODKEY, XK_Insert, spawn, SHCMD("bookmarkmenu")},
    {MODKEY | ShiftMask, XK_Insert, spawn, {.v = (const char *[]){"bookmarkit", NULL}}},

    {MODKEY, XK_w, spawn, {.v = (const char *[]){BROWSER, NULL}}},
    {MODKEY | ShiftMask, XK_w, spawn, SHCMD(TERMINAL " -e nmtui")},

    {MODKEY, XK_e, spawn, {.v = (const char *[]){TERMINAL, "-e", "lfub", NULL}}},
    {MODKEY | ShiftMask, XK_e, spawn, {.v = (const char *[]){TERMINAL, "-e", "bicon", "-e", "neomutt", NULL}}},
    {MODKEY|Mod1Mask, XK_m, spawn, {.v = (const char *[]){TERMINAL, "-e", "bicon", "-e", "ncmpcpp", NULL}}},
    {MODKEY|ShiftMask, XK_r, spawn, {.v = (const char *[]){TERMINAL, "-e", "bicon", "-e", "newsboatpkill", NULL}}},

    {ControlMask, XK_Print, spawn, {.v = (const char *[]){"maimSel", NULL}}},
    {ControlMask | ShiftMask, XK_Print, spawn, {.v = (const char *[]){"maimXclip", NULL}}},
    {0, XK_Print, spawn, {.v = (const char *[]){"maimFul", NULL}}},
    {MODKEY, XK_Print, spawn, {.v = (const char *[]){"dmenurecord", "-i", NULL}}},
    {MODKEY | ShiftMask, XK_Print, spawn, {.v = (const char *[]){"dmenurecord", "kill", NULL}}},
    /* {MODKEY, XK_Scroll_Lock, spawn, {.v = (const char *[]){"pkill", "screenkey", "||", "screenkey", NULL}}}, */

    { 0, XF86XK_AudioMute,		   					spawn,		SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },

    { 0, XF86XK_AudioRaiseVolume,					spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)") },
    { 0, XF86XK_AudioLowerVolume,					spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },
    {0, XF86XK_MonBrightnessUp, spawn, SHCMD("brightnessctl set +10%")},
    {MODKEY, XK_comma, spawn, SHCMD("brightnessctl set 2%-")},
    {MODKEY | ShiftMask, XK_comma, spawn, SHCMD("brightnessctl set 1%")},
    {MODKEY, XK_period, spawn, SHCMD("brightnessctl set +2%")},
    {MODKEY | ShiftMask, XK_period, spawn, SHCMD("brightnessctl set 100%")},
    {0, XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl set -10%")},
    {ShiftMask, XF86XK_MonBrightnessUp, spawn, SHCMD("brightnessctl set +2%")},
    {ShiftMask, XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl set 2%-")},
    {MODKEY, XF86XK_MonBrightnessUp, spawn, SHCMD("brightnessctl set 100%")},
    {MODKEY, XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl set 1%")},

    { MODKEY,			XK_minus,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,		XK_minus,	spawn,		SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
    { MODKEY,			XK_equal,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)") },
    { MODKEY|ShiftMask,		XK_equal,	spawn,		SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 100%; kill -44 $(pidof dwmblocks)") },
    /* {MODKEY | ShiftMask, */ /* XK_p, */ /* spawn, */ /* {.v = (const char *[]){"displayselect", NULL}}}, */
    {MODKEY | ShiftMask, XK_m, spawn, {.v = (const char *[]){"dmenumount", "-i", NULL}}},
    {MODKEY | ShiftMask, XK_q, spawn, {.v = (const char *[]){"sysact", NULL}}},
    {ControlMask | Mod1Mask, XK_Escape, spawn, {.v = (const char *[]){"xkill", NULL}}},
    {MODKEY, XK_BackSpace, spawn, {.v = (const char *[]){"dunstctl", "close-all", NULL}}},
    {MODKEY | ShiftMask, XK_BackSpace, spawn, {.v = (const char *[]){"dunstctl", "history-pop", NULL}}},
    {MODKEY | ControlMask, XK_BackSpace, spawn, {.v = (const char *[]){"dunstctl", "set-paused", "toggle", "&&", "notify-send", "toggled", NULL}}},

    {MODKEY, XK_backslash, spawn, {.v = (const char *[]){"mpc", "repeat", NULL}}},
    {MODKEY | ShiftMask, XK_backslash, spawn, {.v = (const char *[]){"mpc", "seek", "0%", NULL}}},

    {MODKEY, XK_F1, spawn, {.v = (const char *[]){"kdeconnect-indicator", ";", "kdeconnect-cli --refresh", NULL}}},
    {MODKEY | ShiftMask, XK_F1, spawn, SHCMD("kill $(pgrep kdeconnect)")},
    {MODKEY , XK_F2, spawn, {.v = (const char *[]){"redshift", " -O ", " 5000 ", NULL}}},
    {MODKEY | ShiftMask, XK_F2, spawn, SHCMD("redshift -x") },
    {MODKEY, XK_F3, spawn, {.v = (const char *[]){"torwrap", NULL}}},
    {MODKEY | ShiftMask, XK_F3, spawn, {.v = (const char *[]){"td-toggle", NULL}}},
    {MODKEY, XK_F4, spawn, SHCMD("keyboardLogitech && notify-send -t 1000 'Logitech Keyboard Layout Activated'")},
    {MODKEY | ShiftMask, XK_F4, spawn, SHCMD("remaps && xmodmap ~/.config/Xmodmap2 && notify-send -t 1000 'Default Keyboard Layout'")},

    {MODKEY, XK_F11, spawn, {.v = (const char *[]){"mpc", "toggle", NULL}}},
    {MODKEY | ShiftMask, XK_F11, spawn, {.v = (const char *[]){"pauseallmpv", NULL}}},
    {MODKEY, XK_F10, spawn, {.v = (const char *[]){"mpc", "seek", "-1%", NULL}}},
    {MODKEY | ShiftMask, XK_F10, spawn, {.v = (const char *[]){"mpc", "prev", NULL}}},
    {MODKEY, XK_F12, spawn, {.v = (const char *[]){"mpc", "seek", "+1%", NULL}}},
    {MODKEY | ShiftMask, XK_F12, spawn, {.v = (const char *[]){"mpc", "next", NULL}}},

    { MODKEY,               			XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,             				XK_b,      togglebar,      {0} },
	{ MODKEY,                       	XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       	XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_bracketright,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_bracketleft,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       	XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       	XK_l,      setmfact,       {.f = +0.05} },

	{ MODKEY,		                	XK_apostrophe, togglescratch,	{.ui = 0} },

	{ MODKEY,            				XK_g,	shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,					XK_g,		shifttag,	{ .i = -1 } },
	{ MODKEY,			       			XK_semicolon,	shiftview,	{ .i = 1 } },
	{ MODKEY|ShiftMask,					XK_semicolon,	shifttag,	{ .i = 1 } },


	{ MODKEY,			XK_x,	   incrgaps,	{.i = -3 } },
	{ MODKEY|ShiftMask,		XK_x,	   incrgaps,	{.i = +3 } },
	{ MODKEY,                       XK_z,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_z,      defaultgaps,    {0} },
	//	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	//	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	//	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	//	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	//	{ MODKEY,                       XK_x,      incrihgaps,     {.i = +1 } },
	//	{ MODKEY,                       XK_z,      incrihgaps,     {.i = -1 } },
	//	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	//	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	//	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	//	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	//	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	//	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },


	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,           	        XK_space,  zoom,           {0} },
	{ Mod1Mask,                    	XK_Tab,	   focusmaster,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask, 		XK_c,      killclient,     {0} },

	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, //tile
	{ MODKEY,             XK_f,      setlayout,      {.v = &layouts[1]} }, //floating
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, //monocle
	/* { MODKEY,             		XK_u,      setlayout,      {.v = &layouts[3]} }, //deck */
	/* { MODKEY,                       XK_y,      setlayout,      {.v = &layouts[4]} }, //spiral */
	/* { MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[5]} }, // bottomstack */
	/* { MODKEY,                       XK_i,      setlayout,      {.v = &layouts[6]} }, //centeredmaster */


	//	{ MODKEY,           		    XK_BackSpace,  cyclelayout,    {.i = -1 } },

	{ MODKEY|ShiftMask,                       XK_f,      togglefullscreen, {0} },

	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,           	XK_s,  togglecanfocusfloating,   {0} },
	{ MODKEY,             			XK_s,      togglesticky,   {0} },
	//moveresize
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },

	//notitle 2lines
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	/* { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } }, */
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },

	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

