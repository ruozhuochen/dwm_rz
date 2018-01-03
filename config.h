/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
        "terminus:pixelsize=10:antialias=true:autohint=true"
};
static const char dmenufont[]       = "terminus:size=10";  
static const char normbordercolor[] = "#111111"; /* 444444 originally */
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577"; /* 005577 originally */
static const char selbgcolor[]      = "#0055bb"; /* 005577 originally */
static const char selfgcolor[]      = "#eeeeee"; /* eeeeee originally */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, 0: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static void view_adjacent(const Arg *arg);
static const char *upvol[]   = { "amixer", "set", "Master", "3+",     NULL };
static const char *downvol[] = { "amixer", "set", "Master", "3-",     NULL };
static const char *togglevol[] = { "amixer", "-D", "pulse", "set", "Master", "1+", "toggle", NULL };
static const char *upbl[]   = { "xbacklight", "-inc", "9",     NULL };
static const char *downbl[] = { "xbacklight", "-dec", "9",     NULL };

/* tagging */
static const char *tags[] = { "Top", "Term", "Code", "Work", "Mail", "Surf", "Void"};

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,        -1 },
//	{ "Chrome",  NULL,       NULL,       1 << 4,       0,       -1 },
//	{ "Firefox",  NULL,       NULL,       1 << 5,       0,       -1 },
	{ "Eclipse",   NULL,       NULL,       1 << 2,       0,       -1 },
	{ "jetbrains-idea",   NULL,       NULL,       1 << 2,       0,       -1 },
//	{ "Java",   NULL,       NULL,       1 << 4,       0,       -1 },
//	{ "Sublime_text",   NULL,       NULL,       1 << 2,       0,       -1 },
	{ "jetbrains-pycharm",   NULL,       NULL,       1 << 2,       0,       -1 },
	{ "xpad",   NULL,       NULL,       0,    1,       -1 },
	{ "XClock",   NULL,       NULL,       1,    1,       -1 },
	{ "Xmessage",   NULL,       NULL,       NULL,    1,       -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] = { "dmenu_run", "-b", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *xtermcmd[]  = { "xterm", "-geometry", "150x40" };
static const char *slockcmd[]  = { "slock", NULL };
static const char *runSecondMonitor[] = { "SecondMonitorOnly", NULL };
static const char *runBothMonitor[] = { "MatrixMonitors", NULL };
static const char *runLaptopMonitor[] = { "LaptopMonitor", NULL };
static const char *webcmd[]  = { "x-www-browser", NULL };
static const char *skippxdcmd[] = { "skippy-xd", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = xtermcmd } },
	{ MODKEY,		        XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_i,      spawn,          {.v = webcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = skippxdcmd } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,  	   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l, 	   setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

        { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	{ MODKEY,              		XK_Right,           view_adjacent,  { .i = +1 } },
	{ MODKEY,              		XK_Left,           view_adjacent,  { .i = -1 } },
	{ MODKEY,                       XK_F9,    spawn,          {.v = upvol   } },
	{ MODKEY,                       XK_F8,    spawn,          {.v = downvol } },
	{ MODKEY,                       XK_F7,    spawn,          {.v = togglevol } },
	{ MODKEY,                       XK_F3,    spawn,          {.v = upbl   } },
	{ MODKEY,                       XK_F2,    spawn,          {.v = downbl } },
	{ MODKEY|ShiftMask,             XK_l,     spawn,          {.v = slockcmd } },
	{ MODKEY,                       XK_F11,   spawn,          {.v = runSecondMonitor } },
	{ MODKEY,                       XK_F12,   spawn,          {.v = runBothMonitor } },
	{ MODKEY,                       XK_F10,   spawn,          {.v = runLaptopMonitor } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
//	TAGKEYS(                        XK_8,                      7)
//	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
view_adjacent(const Arg *arg)
{
	int i, curtags;
	int seltag = 0;
	Arg a;

	curtags = selmon->tagset[selmon->seltags];
	for(i = 0; i < LENGTH(tags); i++)
		if(curtags & (1 << i)){
			seltag = i;
			break;
		}

	seltag = (seltag + arg->i) % (int)LENGTH(tags);
	if(seltag < 0)
		seltag += LENGTH(tags);

	a.i = (1 << seltag);
	view(&a);
}
