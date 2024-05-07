/* See LICENSE file for copyright and license details. */
// hsluv: clock12: 67, 70, 50
/* appearance */
#ifdef LARGER_FONT
#define DEFAULT_FONT "Hack-11"
#else
#define DEFAULT_FONT "Hack-8"
#endif

static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { DEFAULT_FONT };
static const char dmenufont[]       = DEFAULT_FONT;

#define COL_BLACK "#000000"
#define COL_DARK "#090909"
#define COL_LIGHT "#bf8259"
#define COL_DIM "#444444"

enum { SchemeNorm, SchemeSel, SchemeTagOn, SchemeTagOff }; /* color schemes */

static const char *colors[][3]      = {
  /*                   fg          bg           border   */
  [SchemeNorm]   = { COL_DARK,   COL_LIGHT,   COL_BLACK },
  [SchemeSel]    = { COL_LIGHT,  COL_DARK,    COL_LIGHT },
  [SchemeTagOn]  = { COL_LIGHT,  COL_DARK,    COL_LIGHT },
  [SchemeTagOff] = { COL_DIM,    COL_DARK,    COL_LIGHT },
};

static const char *const autostart[] = {
  "sh", "-c", "feh --randomize --bg-max /home/indy/gdrive/art/*", NULL,
  "dwm-bar", NULL,
  "emacs", NULL,
  "brave", NULL,
  NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const char ptagf[] = "[%s %s]";  /* format of a tag label */
static const char etagf[] = "[%s]";  /* format of an empty tag */
static const int lcaselbl = 0;    /* 1 means make tag label lowercase */

static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class               instance    title       tags mask     switchtotag isfloating   monitor */
  /* { "firefox",           NULL,       NULL,       1 << 0,       1,          0,           -1 }, */
  { "Brave-browser",     NULL,       NULL,       1 << 0,       1,          0,           -1 },
  { "Emacs",             NULL,       NULL,       1 << 1,       1,          0,           -1 },
  { "calibre",           NULL,       NULL,       1 << 2,       1,          0,           -1 },
  { "Tor Browser",       NULL,       NULL,       1 << 3,       1,          0,           -1 },
  { "Gimp",              NULL,       NULL,       1 << 4,       1,          1,           -1 },
  { "Steam",             NULL,       NULL,       1 << 5,       1,          0,           -1 },
  { "Chromium-browser",  NULL,       NULL,       1 << 8,       1,          0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.35; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "|M|",      centeredmaster }, /* first entry is default */
  { "=[]",      tile },
  { "><>",      NULL },    /* no layout function means floating behavior */
  { "(M)",      monocle },
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
static const char *refreshbarcmd[] = { "dwm-bar-update", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *wallpapercmd[]  = { "sh", "-c", "feh --randomize --bg-max /home/indy/gdrive/art/*", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static const char *audiotogglecmd[] = { "dwm-audio", "toggle", NULL };
static const char *audiodeccmd[]    = { "dwm-audio", "dec", NULL };
static const char *audioinccmd[]    = { "dwm-audio", "inc", NULL };
static const char *audioplaycmd[]   = { "dwm-audio", "playpause", NULL };
static const char *audioprevcmd[]   = { "dwm-audio", "prev", NULL };
static const char *audionextcmd[]   = { "dwm-audio", "next", NULL };

static Key keys[] = {
  /* modifier           key                      function        argument */
  { MODKEY,             XK_r,                    spawn,          {.v = refreshbarcmd } },
  { MODKEY,             XK_d,                    spawn,          {.v = commondmenucmd } },
  { MODKEY|ShiftMask,   XK_d,                    spawn,          {.v = dmenucmd } },
  { MODKEY|ShiftMask,   XK_Return,               spawn,          {.v = termcmd } },
  { MODKEY,             XK_grave,                togglescratch,  {.v = scratchpadcmd } },
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
  { MODKEY,             XK_Tab,                  tabswitch,      {0} },
  { MODKEY|ShiftMask,   XK_q,                    killclient,     {0} },
  { MODKEY,             XK_f, /* fullscreen */   togglefullscreen, {0} },
  { MODKEY,             XK_u, /* centered */     setlayout,      {.v = &layouts[0]} },
  { MODKEY,             XK_t, /* tile     */     setlayout,      {.v = &layouts[1]} },
  { MODKEY|ShiftMask,   XK_f, /* float    */     setlayout,      {.v = &layouts[2]} },
  { MODKEY,             XK_s, /* single   */     setlayout,      {.v = &layouts[3]} },
  // audio controls
#if 0
  { MODKEY,             XK_v,                    spawn,          {.v = audioplaycmd } },
  { MODKEY,             XK_b,                    spawn,          {.v = audioprevcmd } },
  { MODKEY,             XK_n,                    spawn,          {.v = audionextcmd } },
#endif
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
  { MODKEY,             XK_w,                    spawn,          {.v = wallpapercmd } },
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
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
