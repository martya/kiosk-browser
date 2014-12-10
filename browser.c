#include <stdio.h>
#include <signal.h>

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <webkit/webkit.h>
#include <getopt.h>

gboolean on_key_press(GtkWidget*, GdkEventKey*, gpointer);

void reload_browser(int);
void maximize();

static WebKitWebSettings *settings;
static WebKitWebView* web_view;
static GtkWidget *window;
static GdkScreen *screen;
static GtkWidget *scrolledWindow;
gint width = 0, height = 0, opt = 0, scrolled = 0;
gchar* default_url = "https://github.com/pschultz/kiosk-browser/blob/master/README.md";

int main(int argc, char** argv) {
	gtk_init(&argc, &argv);

	screen = gdk_screen_get_default();
	width = gdk_screen_get_width(screen);
	height = gdk_screen_get_height(screen);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), width, height);

	scrolledWindow = gtk_scrolled_window_new(NULL, NULL);

	g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());

	/* Setting the User Agent*/
	settings = webkit_web_view_get_settings(web_view);
	g_object_set(settings, "user-agent", "kiosk-browser/0.1", NULL);

	signal(SIGHUP, reload_browser);

	//Options
	static struct option long_options[] = {
			{ "url", required_argument, 0, 'u' },
			{ "scrolled", no_argument, 0, 's' },
			{ 0, 0, 0, 0 }
	};

	int long_index = 0;

	while ((opt = getopt_long(argc, argv, "u:s",
		long_options, &long_index)) != -1) {
		switch (opt) {
		case 'u': default_url = optarg;
			break;
		case 's': scrolled = 1;
			break;
		default:;
		}
	}

	if (scrolled == 1) {
		gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(scrolledWindow));
		gtk_container_add(GTK_CONTAINER(scrolledWindow), GTK_WIDGET(web_view));
	}
	else	{
		gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(web_view));
	}

	webkit_web_view_load_uri(web_view, default_url);

	maximize();
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}

gboolean on_key_press(GtkWidget* window, GdkEventKey* key, gpointer userdata) {
	if (key->type == GDK_KEY_PRESS && key->keyval == GDK_KEY_F5) {
		reload_browser(0);
	}

	return FALSE;
}

void reload_browser(int signum) {
	webkit_web_view_reload_bypass_cache(web_view);
}

void maximize() {
	gtk_window_maximize(GTK_WINDOW(window));
	gtk_window_fullscreen(GTK_WINDOW(window));
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
}
