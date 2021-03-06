/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "GoMono Nerd Font", "Noto Serif CJK SC" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { " ", " ", "ﳑ ", " ", " ", " ", " ", " ", " " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance   title         tags mask   switchtotag   iscentered     isfloating   isterminal noswallow monitor */
	{ "Pavucontrol",  NULL,      NULL,         0,          0,            1,             1,           0,         0,        -1 },
	{ "Arandr",       NULL,      NULL,         0,          0,            1,             1,           0,         0,        -1 },
	{ "feh",          NULL,      NULL,         0,          0,            1,             1,           0,         0,        -1 },
	{ "Galculator",   NULL,      NULL,         0,          0,            1,             1,           0,         0,        -1 },
	{ "Gsimplecal",   NULL,      NULL,         0,          0,            1,             1,           0,         0,        -1 },
	{ "Gcr-prompter", NULL,      NULL,         0,          0,            1,             1,           0,         0,        -1 },
	{ "EasyConnect",  NULL,      NULL,         0,          0,            0,             1,           0,         0,        -1 },
	{ "mpv",          NULL,      NULL,         1 << 6,     1,            0,             0,           0,         0,        -1 },
	{ "St",           NULL,      NULL,         0,          0,            0,             0,           1,         0,        -1 },
	{ "St",           NULL,      "neomutt",    1 << 8,     1,            0,             0,           0,         0,        -1 },
	{ "St",           NULL,      "pulsemixer", 0,          0,            1,             1,           0,         0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "gaplessgrid.c"
#include "movestack.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile }, /* first entry is default */
	{ "###",      gaplessgrid },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define CMD(cmd) { .v = (const char*[]){ cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-i", "-l", "5", "-c", "-p", "Run", NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"
#include "tagadjacent.c"
static Key keys[] = {
	/* modifier,         key,                       function,  argument */
	/* applications */
	{ MODKEY,            XK_a,                      spawn,     {.v = dmenucmd } },
	{ MODKEY,            XK_Return,                 spawn,     {.v = termcmd } },
	{ MODKEY,            XK_w,                      spawn,     CMD("chromium") },
	{ MODKEY,            XK_v,                      spawn,     SHCMD("st -t pulsemixer -e pulsemixer") },
	{ MODKEY|ShiftMask,  XK_Return,                 spawn,     CMD("pcmanfm") },
	{ MODKEY|ShiftMask,  XK_m,                      spawn,     SHCMD("st -t neomutt -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ MODKEY,            XK_m,                      spawn,     SHCMD("mw -Y") },
	{ MODKEY,            XK_e,                      spawn,     SHCMD("open-dmenu") },
	{ MODKEY,            XK_p,                      spawn,     SHCMD("display-dmenu") },
	/* sound light control */
	{ 0,                 XF86XK_AudioMute,          spawn,     SHCMD("volume --togmute") },
	{ 0,                 XF86XK_AudioRaiseVolume,   spawn,     SHCMD("volume --up") },
	{ 0,                 XF86XK_AudioLowerVolume,   spawn,     SHCMD("volume --down") },
	{ MODKEY,            XK_0,                      spawn,     SHCMD("volume --togmute") },
	{ MODKEY,            XK_equal,                  spawn,     SHCMD("volume --up") },
	{ MODKEY,            XK_minus,                  spawn,     SHCMD("volume --down") },
	{ 0,                 XF86XK_MonBrightnessUp,    spawn,     SHCMD("xbacklight -inc 10") },
	{ 0,                 XF86XK_MonBrightnessDown,  spawn,     SHCMD("xbacklight -dec 10") },
	/* dmenu scripts */
	{ MODKEY,            XK_d,                      spawn,     CMD("dpi-dmenu") },
	{ MODKEY,            XK_x,                      spawn,     CMD("logout-dmenu") },
	{ MODKEY,            XK_s,                      spawn,     CMD("restartsvc.sh") },
	{ MODKEY|ShiftMask,  XK_s,                      spawn,     SHCMD("restartsvc.sh --force") },
	{ MODKEY,            XK_n,                      spawn,     CMD("iwd-dmenu") },
	{ MODKEY|ShiftMask,  XK_n,                      spawn,     CMD("iwd-restart") },
	{ MODKEY|ShiftMask,  XK_u,                      spawn,     CMD("mount-dmenu") },
	{ MODKEY,            XK_u,                      spawn,     CMD("umount-dmenu") },
	{ MODKEY,            XK_semicolon,              spawn,     SHCMD("checklock --force") },
	{ 0,                 XK_Print,                  spawn,     CMD("printscreen-dmenu") },
	/* workspace navigation */
	{ MODKEY,                       XK_l,      shiftview,       {.i = +1 } },
	{ MODKEY,                       XK_h,      shiftview,       {.i = -1 } },
	/* window navigation & move */
	{ MODKEY,                       XK_j,      focusstack,      {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,       {.i = -1 } },
	{ MODKEY,                       XK_y,      tagtoleft,       {0} },
	{ MODKEY,                       XK_o,      tagtoright,      {0} },
	/* window control */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating,  {0} },
	{ MODKEY,                       XK_f,      togglefullscr,   {0} },
	{ MODKEY,                       XK_z,      killclient,      {0} },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	/* layout control */
	{ MODKEY|ControlMask,           XK_t,      setlayout,       {.v = &layouts[0]} },
	{ MODKEY|ControlMask,           XK_g,      setlayout,       {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_f,      setlayout,       {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_m,      setlayout,       {.v = &layouts[3]} },
	{ MODKEY|ControlMask,           XK_space,  setlayout,       {0} },
	/* workspace navigation */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	/* gaps control */
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_0,      setgaps,        {.i = 0  } },
	/* monitor control */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        /* dwm control */
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	/* not used */
	/* { MODKEY,                       XK_b,      togglebar,      {0} }, */
	/* { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } }, */
	/* { MODKEY|ControlMask,           XK_Return, zoom,           {0} }, */
	/* { MODKEY,                       XK_Tab,    view,           {0} }, */
	/* { MODKEY|ShiftMask,             XK_0,      view,           {.ui = ~0 } }, */
	/* { MODKEY|ControlMask,           XK_0,      tag,            {.ui = ~0 } }, */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

