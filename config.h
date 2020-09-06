/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cpu_perc            cpu usage in percent            NULL
 * cpu_freq            cpu frequency in MHz            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/")
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 */

static const char vol[]         = "a=$(amixer get Master | tail -n 1 | cut -d ' '\
                                -f 8); if [ $a = '[on]' ]; then printf \"$(amixer \
                                get Master | tail -n 1 | cut -d ' ' -f 7 | \
                                grep -Po '\\[\\K[^%]*')%%\"; \
                                else printf 'Off'; fi";

static const char mic[]         = "a=$(amixer get Capture | tail -n 1 | cut -d ' '\
                                -f 8); if [ $a == '[on]' ]; then printf \"$(amixer \
                                get Capture | tail -n 1 | cut -d ' ' -f 7 | \
                                grep -Po '\\[\\K[^%]*')%%\"; \
                                else printf 'Off'; fi";

static const char perc_light[]          = "xbacklight -get";
static const char filetemp[]            = "/sys/class/thermal/thermal_zone0/temp";

static const struct arg args[] = {
        /* function format          argument */
        { uptime,       "|:%s|",       NULL }, /* Uptime */
        { temp,         "⚛:%s°C|",      filetemp }, /* Temperature. */
        { cpu_perc,     ":%s%%|",      NULL }, /* CPU used percent. */
        { ram_used,     ":%s",         NULL }, /* Free RAM. */
        { ram_total,    "/%s|",         NULL }, /* Total RAM. */
        { run_command,  ":%s%%|",      perc_light }, /* Display light percentage. */
        { battery_perc, ":%s%% ",      "BAT0" }, /* Battery percent. */
        { battery_state,"%s|",          "BAT0" }, /* Battery state. */
        { run_command,  ":%s|",        vol }, /* Volume percent. */
        { run_command,  ":%s|",        mic }, /* Microphone percent. */
        { keymap,       "⌨:%s|",        NULL }, /* Keyboard layout */
        { datetime,     ":%s|",        "%T" }, /* Date time with this format: Day name YYYY-MM-DD 18:00:00 */
};
