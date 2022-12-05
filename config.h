/* See LICENSE file for copyright and license details. */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "firefox"
#define BROWSERCLASS "firefox"

/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int systraypinning =
  0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
        X */
static const unsigned int systrayonleft =
  0; /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst =
  1; /* 1: if pinning fails, display systray on the first monitor, False:
        display systray on the last monitor*/
static const int showsystray = 1; /* 0 means no systray */
static const int showbar = 1;     /* 0 means no bar */
static const int topbar = 1;      /* 0 means bottom bar */
static const char *fonts[] = {"Mono:pixelsize=13"};
static const char normfgcolor[]           = "#bbbbbb";
static const char normbgcolor[]           = "#222222";
static const char normbordercolor[]       = "#444444";
static const char selfgcolor[]            = "#eeeeee";
static const char selbgcolor[]            = "#005577";
static const char selbordercolor[]        = "#09e47c";
static const char *colors[][3] = {
  /*               fg           bg           border   */
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "100x30", NULL };
const char *spcmd3[] = {"keepassxc", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
};



static const Rule rules[] = {
  /* xprop(1):
   *	WM_CLASS(STRING) = instance, class
   *	WM_NAME(STRING) = title
   */
  /* class      instance    title       tags mask     isfloating   monitor */
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
  {"Emacs", NULL, NULL, 1 << 2, 0, -1},
  {"jetbrains-idea-ce", NULL, NULL, 1 << 3, 0, -1},
  {"java-util-concurrent-ForkJoinWorkerThread", NULL, NULL, 1 << 3, 0, -1},
  {NULL, NULL, "Eclipse", 1 << 3, 0, -1},
  {NULL, NULL, "LibreOffice", 1 << 6, 0, -1},
  {"Gimp", NULL, NULL, 1 << 5, 0, -1},
  {"TelegramDesktop", NULL, NULL, 1 << 4, 0, -1},
	{ NULL,		  "spterm",		NULL,		SPTAG(0),		1,			 -1 },
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
  0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
  1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
  /* symbol     arrange function */
  {"[]=", tile}, /* first entry is default */
  {"><>", NULL}, /* no layout function means floating behavior */
  {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                               \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},        \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                 \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

#include <X11/XF86keysym.h>
// #include "shift-tools.c"

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                        \
  {                                                       \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }  \
  }

/* commands */
static const char *termcmd[] = {"st", NULL};

static const Key keys[] = {
  /* modifier                     key        function        argument */
  {MODKEY,
   XK_p,
   spawn ,
   {.v = (const char *[]){"dmenu_run", NULL}}},
  {MODKEY, XK_Return, spawn, {.v = termcmd}},
  { MODKEY,                       XK_apostrophe,  togglescratch,  {.ui = 0 } },
  {MODKEY, XK_b, togglebar, {0}},
  {MODKEY, XK_j, focusstack, {.i = +1}},
  {MODKEY, XK_k, focusstack, {.i = -1}},
  /* {MODKEY, XK_i, incnmaster, {.i = +1}}, */
  /* {MODKEY, XK_d, incnmaster, {.i = -1}}, */
  { MODKEY|ShiftMask,                       XK_s,      togglecanfocusfloating,   {0} },
  {MODKEY, XK_h, setmfact, {.f = -0.05}},
  {MODKEY, XK_l, setmfact, {.f = +0.05}},
  {MODKEY, XK_space, zoom, {0}},
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
  {MODKEY, XK_Tab, view, {0}},
  {MODKEY | ShiftMask, XK_c, killclient, {0}},
  {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
  {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
  {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
  { MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
  // {MODKEY | ShiftMask, XK_f, setlayout, {0}},
  {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
  {MODKEY|ShiftMask, XK_0, view, {.ui = ~0}},
  /* {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}}, */
  {MODKEY, XK_bracketleft, focusmon, {.i = -1}},
  {MODKEY, XK_bracketright, focusmon, {.i = +1}},
  {MODKEY | ShiftMask, XK_bracketleft, tagmon, {.i = -1}},
  {MODKEY | ShiftMask, XK_bracketright, tagmon, {.i = +1}},
  TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
  TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
  TAGKEYS(XK_9, 8)
  // {MODKEY | ShiftMask, XK_q, quit, {0}},
  // My keybindings
  {MODKEY | ShiftMask,
   XK_d,
   spawn,
   {.v = (const char *[]){"dmenuhandlerXclip", NULL}}},
  /* {MODKEY | ShiftMask, XK_d, spawn, */
  /* SHCMD(TERMINAL " -e nvim ~/stuff/wiki/diary")}, */
  {MODKEY | ShiftMask, XK_p, spawn, {.v = (const char
                                           *[]){"passmenu", NULL}}},
  {MODKEY,
   XK_v,
   spawn,
   {.v = (const char *[]){"clipmenu", "-i", "-l", "15", NULL}}},
  {MODKEY | ShiftMask,
   XK_v,
   spawn,
   {.v = (const char *[]){TERMINAL, "-e", "pulsemixer", NULL}}},
  {MODKEY,
   XK_grave,
   spawn,
   {.v = (const char *[]){"dmenuunicode", "-i", NULL}}},
  {MODKEY, XK_i, spawn, {.v = (const char *[]){"emacs", NULL}}},
  {MODKEY | Mod1Mask,
   XK_slash,
   spawn,
   {.v = (const char *[]){TERMINAL, "-e", "transs", NULL}}},
  // {Mod1Mask, XK_space, spawn, //  SHCMD(" xkb-switch --next; pkill
  // -RTMIN+21 dwmblocks ;")},
  {MODKEY, XK_slash, spawn, {.v = (const char *[]){"transXclip", NULL}}},
  {MODKEY | ShiftMask,
   XK_slash,
   spawn,
   {.v = (const char *[]){"transXcclip", NULL}}},
  {MODKEY, XK_Insert, spawn, SHCMD("bookmarkmenu")},
  {MODKEY | ShiftMask,
   XK_Insert,
   spawn,
   {.v = (const char *[]){"bookmarkit", NULL}}},
	// { MODKEY,			XK_semicolon,		shiftviewclients,	{ .i = +1 } },
	// { MODKEY|ShiftMask,			XK_semicolon,		shifttagclients,	{ .i = +1 } },
	// { MODKEY,			XK_g,		shiftviewclients,	{ .i = -1 } },
 //  { MODKEY|ShiftMask,             XK_g, shifttagclients,    { .i = -1 } },

  {MODKEY, XK_w, spawn, {.v = (const char *[]){BROWSER, NULL}}},
  {MODKEY | ShiftMask, XK_w, spawn, SHCMD(TERMINAL " -e nmtui")},

  {MODKEY,
   XK_e,
   spawn,
   {.v = (const char *[]){TERMINAL, "-e", "lfub", NULL}}},
  {MODKEY | ShiftMask,
   XK_e,
   spawn,
   {.v = (const char *[]){TERMINAL, "-e", "bicon", "-e", "neomutt",
                          NULL}}},
  {MODKEY|Mod1Mask, XK_m, spawn, {.v = (const char *[]){TERMINAL, "-e",
                                                        "bicon", "-e", "ncmpcpp", NULL}}},
  {MODKEY|ShiftMask,
   XK_r,
   spawn,
   {.v = (const char *[]){TERMINAL, "-e", "bicon", "-e", "newsboatpkill",
                          NULL}}},

  {ControlMask, XK_Print, spawn, {.v = (const char *[]){"maimSel", NULL}}},
  {ControlMask | ShiftMask,
   XK_Print,
   spawn,
   {.v = (const char *[]){"maimXclip", NULL}}},
  {0, XK_Print, spawn, {.v = (const char *[]){"maimFul", NULL}}},
  {MODKEY,
   XK_Print,
   spawn,
   {.v = (const char *[]){"dmenurecord", "-i", NULL}}},
  {MODKEY | ShiftMask,
   XK_Print,
   spawn,
   {.v = (const char *[]){"dmenurecord", "kill", NULL}}},
  /* {MODKEY, XK_Scroll_Lock, spawn, {.v = (const char *[]){"pkill",
     "screenkey", "||", "screenkey", NULL}}}, */

  {0, XF86XK_AudioMute, spawn,
   SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)")},
  {0, XF86XK_AudioRaiseVolume, spawn,
   SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)")},
  {0, XF86XK_AudioLowerVolume, spawn,
   SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)")},
  {0,
   XF86XK_MonBrightnessUp,
   spawn,
 SHCMD("brightnessctl set +10%")},
  {MODKEY,
   XK_comma,
   spawn,
 SHCMD("brightnessctl set 2%-")},
  {MODKEY | ShiftMask,
   XK_comma,
   spawn,
 SHCMD("brightnessctl set 1%")},
  {MODKEY,
   XK_period,
   spawn,
 SHCMD("brightnessctl set +2%")},
  {MODKEY | ShiftMask,
   XK_period,
   spawn,
 SHCMD("brightnessctl set 100%")},
  {0,
   XF86XK_MonBrightnessDown,
   spawn,
 SHCMD("brightnessctl set -10%")},
  {ShiftMask,
   XF86XK_MonBrightnessUp,
   spawn,
 SHCMD("brightnessctl set +2%")},
  {ShiftMask,
   XF86XK_MonBrightnessDown,
   spawn,
 SHCMD("brightnessctl set 2%-")},
  {MODKEY,
   XF86XK_MonBrightnessUp,
   spawn,
 SHCMD("brightnessctl set 100%")},
  {MODKEY,
   XF86XK_MonBrightnessDown,
   spawn,
 SHCMD("brightnessctl set 1%")},

  {MODKEY, XK_minus, spawn,
   SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)")},
  {MODKEY | ShiftMask, XK_minus, spawn,
   SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)")},
  {MODKEY, XK_equal, spawn,
   SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)")},
  {MODKEY | ShiftMask, XK_equal, spawn,
   SHCMD("pamixer --set-volume 100; kill -44 $(pidof dwmblocks)")},
  // { MODKEY|ShiftMask,			XK_m,			spawn, // SHCMD("pamixer
  // -t; kill -44
  // //
  // $(pidof dwmblocks)") },
  /* {MODKEY | ShiftMask, */
  /* XK_p, */
  /* spawn, */
  /* {.v = (const char *[]){"displayselect", NULL}}}, */
  {MODKEY | ShiftMask,
   XK_m,
   spawn,
   {.v = (const char *[]){"dmenumount", "-i", NULL}}},

  {MODKEY | ShiftMask, XK_q, spawn, {.v = (const char *[]){"sysact", NULL}}},
  {ControlMask | Mod1Mask,
   XK_Escape,
   spawn,
   {.v = (const char *[]){"xkill", NULL}}},
  {MODKEY,
   XK_BackSpace,
   spawn,
   {.v = (const char *[]){"dunstctl", "close-all", NULL}}},
  {MODKEY | ShiftMask,
   XK_BackSpace,
   spawn,
   {.v = (const char *[]){"dunstctl", "history-pop", NULL}}},
  {MODKEY | ControlMask,
   XK_BackSpace,
   spawn,
   {.v = (const char *[]){"dunstctl", "set-paused", "toggle", "&&",
                          "notify-send", "toggled", NULL}}},

  {MODKEY, XK_F11, spawn, {.v = (const char *[]){"mpc", "toggle", NULL}}},
  {MODKEY | ShiftMask,
   XK_F11,
   spawn,
   {.v = (const char *[]){"pauseallmpv", NULL}}},
  {MODKEY,
   XK_F10,
   spawn,
   {.v = (const char *[]){"mpc", "seek", "-1%", NULL}}},
  {MODKEY | ShiftMask,
   XK_F10,
   spawn,
   {.v = (const char *[]){"mpc", "prev", NULL}}},
  {MODKEY,
   XK_F12,
   spawn,
   {.v = (const char *[]){"mpc", "seek", "+1%", NULL}}},
  {MODKEY | ShiftMask,
   XK_F12,
   spawn,
   {.v = (const char *[]){"mpc", "next", NULL}}},
  {MODKEY,
   XK_backslash,
   spawn,
   {.v = (const char *[]){"mpc", "repeat", NULL}}},
  {MODKEY | ShiftMask,
   XK_backslash,
   spawn,
   {.v = (const char *[]){"mpc", "seek", "0%", NULL}}},

  {MODKEY,
   XK_F1,
   spawn,
   {.v = (const char *[]){"kdeconnect-indicator", ";",
                          "kdeconnect-cli --refresh", NULL}}},
  {MODKEY | ShiftMask, XK_F1, spawn, SHCMD("kill $(pgrep kdeconnect)")},
  {MODKEY,
   XK_F4,
   spawn,
   {.v = (const char *[]){"keyboardLogitech", NULL}}},
  {MODKEY | ShiftMask,
   XK_F4,
   spawn,
   {.v = (const char *[]){"xmodmap ", " &&",  "~/.config/Xmodmap", NULL}}},
  {MODKEY ,
   XK_F2,
   spawn,
   {.v = (const char *[]){"redshift", " -O ", " 5000 ", NULL}}},
  {MODKEY, XK_F3, spawn, {.v = (const char *[]){"torwrap", NULL}}},
  {MODKEY | ShiftMask,
   XK_F2,
   spawn,
   {.v = (const char *[]){"redshift", " -x", NULL}}},
  {MODKEY, XK_F3, spawn, {.v = (const char *[]){"torwrap", NULL}}},
  {MODKEY | ShiftMask,
   XK_F3,
   spawn,
   {.v = (const char *[]){"td-toggle", NULL}}},

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
  /* click                event mask      button          function argument */
  {ClkTagBar, MODKEY, Button1, tag, {0}},
  {ClkTagBar, MODKEY, Button3, toggletag, {0}},
  {ClkWinTitle, 0, Button2, zoom, {0}},
  {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
  {ClkClientWin, MODKEY, Button1, movemouse, {0}},
  {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
  {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
  {ClkTagBar, 0, Button1, view, {0}},
  {ClkTagBar, 0, Button3, toggleview, {0}},
  {ClkTagBar, MODKEY, Button1, tag, {0}},
  {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};

