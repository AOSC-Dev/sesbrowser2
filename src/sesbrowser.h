#include <webkit2/webkit2.h>
#include <JavaScriptCore/JavaScript.h> 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class SESdotJS
{
	private:
/*	static void SES_Initialize(JSContextRef ctx, JSObjectRef object);
	static void SES_Finalize(JSObjectRef object);
	static JSValueRef SES_GetVerbose(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef *exception);
	static JSValueRef SES_GetVersion(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef *exception);
	static JSValueRef SES_Show(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception);
	static JSValueRef SES_Print(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception);*/
	static JSClassRef SES_ClassCreate(JSContextRef ctx);
	
	public:
	SESdotJS (JSGlobalContextRef ctx);
};

class BrowserAction
{
	private:
	WebKitWebView* view;
	
	public:
	static int num;

	static GtkWidget* signal_create (WebKitWebView* web_view, WebKitNavigationAction *navigation_action, gpointer browser);
	static void signal_ready_to_show (WebKitWebView* web_view, gpointer data);
	static gboolean signal_enter_fullscreen (WebKitWebView *web_view, GtkWidget* window);
	static gboolean signal_leave_fullscreen (WebKitWebView *web_view, GtkWidget* window);
	static void signal_close (WebKitWebView* web_view, gpointer data);
	static void web_view_load_changed(WebKitWebView  *web_view, WebKitLoadEvent load_event, gpointer user_data);
	static void win_signal_close (GtkWidget* win, gpointer data);
	
	static void num_dec ();
	
	static void close (GtkWidget* w);
	void init (WebKitWebView* view, gpointer b, gpointer w);
};

class MainWindow
{
	public:
	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	GtkWidget* scroll = gtk_scrolled_window_new (NULL, NULL);
	GtkWidget* headerbar = gtk_header_bar_new ();
	GtkWidget* webview;
	BrowserAction action;
	
	void load_uri (char* str);
	void show_basic ();
	GtkWidget* get_View ();
	
	void create_webview (GtkWidget* old);
	
	MainWindow (int width, int height, GtkWidget* old, gpointer b);
};

class SESBrowser
{
	public:
	MainWindow* 	window;    // FIXME: How do we free the slots?
	gboolean*		available; 
	
	int whoIs (GtkWidget* win);
	int getAvailable ();
	
	GtkWidget* newWindow (char* uri, GtkWidget* old);
	
	SESBrowser (char* uri, GtkWidget* old);

	private:
	static const int maxWindows = 128; // we don't need it to be public, right?
};

// very trivial, inlinable functions -- moved from prog cpp.
inline int SESBrowser::getAvailable ()
{
	for (int i=0; i < maxWindows; i++)
	{
		if (this->available[i] == TRUE)
		{
			return i;
		}
	}
	return -1;
}

inline int SESBrowser::whoIs (GtkWidget* win)
{
	for (int i=0; i < maxWindows; i++)
	{
		if (this->window[i].window == win)
		{
			return i;
		}
	}
	return -1;
}

