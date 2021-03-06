/* See LICENSE file for copyright and license details. */
// hsluv: clock12: 67, 70, 50
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack-11" };
static const char dmenufont[]       = "Hack-11";

#define MONO_BG "#090909"
#define MONO_FG "#dd9d5c"
static const char col_dark[]        = MONO_BG; // bg0 from athens theme
static const char col_light[]       = MONO_FG;
static const char col_hi[]          = MONO_FG;

static const char col_dark_border[] = "#000000";
static const char col_hi_border[]   = MONO_FG;

enum { SchemeNorm, SchemeSel }; /* color schemes */

static const char *colors[][3]      = {
  /*                fg          bg        border   */
  [SchemeNorm]  = { col_dark,   col_hi,   col_dark_border },
  [SchemeSel]   = { col_light,  col_dark, col_hi_border },
};

static const char *const autostart[] = {
  "sh", "-c", "while :; do feh --randomize --bg-max /home/indy/gdrive/art/* -; sleep 30m; done", NULL,
	"dwmblocks", NULL,
#if 0
  "emacs", NULL,
  "brave-browser", NULL,
#endif
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class               instance    title       tags mask     isfloating   monitor */
	{ "Gimp",              NULL,       NULL,       0,            1,           -1 },
#if 0
	{ "Emacs",             NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Brave-browser",     NULL,       NULL,       1 << 0,       0,           -1 },
	{ "Chromium-browser",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Firefox",           NULL,       NULL,       1 << 8,       0,           -1 },
#endif
};

/* layout(s) */
static const float mfact     = 0.35; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "|M|",      centeredmaster }, /* first entry is default */
	{ "=[]",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *commondmenucmd[] = { "dmenu_run_common", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "st", NULL };

static const char *audiotogglecmd[] = { "dwm-audio", "toggle", NULL };
static const char *audiodeccmd[]    = { "dwm-audio", "dec", NULL };
static const char *audioinccmd[]    = { "dwm-audio", "inc", NULL };
static const char *audioplaycmd[]   = { "dwm-audio", "playpause", NULL };
static const char *audioprevcmd[]   = { "dwm-audio", "prev", NULL };
static const char *audionextcmd[]   = { "dwm-audio", "next", NULL };

static Key keys[] = {
	/* modifier           key                      function        argument */
	{ MODKEY,             XK_d,                    spawn,          {.v = commondmenucmd } },
	{ MODKEY|ShiftMask,   XK_d,                    spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,   XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY,             XK_space,                togglebar,      {0} }, // the obvious key for togglebar
	{ MODKEY,             XK_j,                    focusstack,     {.i = +1 } },
	{ MODKEY,             XK_k,                    focusstack,     {.i = -1 } },
	{ ALTKEY,             XK_0,                    focusstack,     {.i = +1 } }, // emacs finger memory
#if 0
	{ MODKEY,             XK_i,                    incnmaster,     {.i = +1 } },
	{ MODKEY,             XK_d,                    incnmaster,     {.i = -1 } },
#endif
	{ MODKEY,             XK_h,                    setmfact,       {.f = -0.05} },
	{ MODKEY,             XK_l,                    setmfact,       {.f = +0.05} },
	{ MODKEY,             XK_Return,               zoom,           {0} },
	{ ALTKEY,             XK_Return,               zoom,           {0} }, // emacs typo prevention
#if 0
	{ MODKEY,             XK_Tab,                  view,           {0} },
#endif
	{ MODKEY|ShiftMask,   XK_q,                    killclient,     {0} },
	{ MODKEY,             XK_f, /* fullscreen */   togglefullscreen, {0} },

	{ MODKEY,             XK_u, /* centered */     setlayout,      {.v = &layouts[0]} },
	{ MODKEY,             XK_t, /* tile     */     setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,   XK_f, /* float    */     setlayout,      {.v = &layouts[2]} },
	{ MODKEY,             XK_s, /* single   */     setlayout,      {.v = &layouts[3]} },
  // audio controls
  { MODKEY,             XK_v,                    spawn,          {.v = audioplaycmd } },
  { MODKEY,             XK_b,                    spawn,          {.v = audioprevcmd } },
  { MODKEY,             XK_n,                    spawn,          {.v = audionextcmd } },
  { MODKEY,             XK_m,                    spawn,          {.v = audiotogglecmd } },
  { MODKEY,             XK_comma,                spawn,          {.v = audiodeccmd } },
  { MODKEY,             XK_period,               spawn,          {.v = audioinccmd } },
  { 0,                  XF86XK_AudioPlay,        spawn,          {.v = audioplaycmd } },
  { 0,                  XF86XK_AudioPause,       spawn,          {.v = audioplaycmd } },
  { 0,                  XF86XK_AudioPrev,        spawn,          {.v = audioprevcmd } },
  { 0,                  XF86XK_AudioNext,        spawn,          {.v = audionextcmd } },
  { 0,                  XF86XK_AudioMute,        spawn,          {.v = audiotogglecmd } },
  { 0,                  XF86XK_AudioLowerVolume, spawn,          {.v = audiodeccmd } },
  { 0,                  XF86XK_AudioRaiseVolume, spawn,          {.v = audioinccmd } },
#if 0
	{ MODKEY,             XK_space,                setlayout,      {0} }, // key taken by togglebar
#endif
	{ MODKEY|ShiftMask,   XK_space,                togglefloating, {0} },
#if 0
	{ MODKEY,             XK_0,                    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,   XK_0,                    tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,   XK_comma,                tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,   XK_period,               tagmon,         {.i = +1 } },
#endif
	TAGKEYS(              XK_1,                                    0)
	TAGKEYS(              XK_2,                                    1)
	TAGKEYS(              XK_3,                                    2)
	TAGKEYS(              XK_4,                                    3)
	TAGKEYS(              XK_5,                                    4)
	TAGKEYS(              XK_6,                                    5)
	TAGKEYS(              XK_7,                                    6)
	TAGKEYS(              XK_8,                                    7)
	TAGKEYS(              XK_9,                                    8)
	{ MODKEY|ShiftMask,   XK_e, /* exit dwm */     quit,           {0} },
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
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
