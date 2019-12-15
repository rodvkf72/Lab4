#include <gtk/gtk.h>
#include <stdio.h>
GtkWidget *checkbutton;
GtkWidget *togglebutton;
GtkWidget *radiobutton1, *radiobutton2;
void quit ( GtkWidget *window, gpointer data)
{
gtk_main_quit();
}
void add_widget_with_label ( GtkContainer * box,
gchar * caption, GtkWidget * widget)
{
GtkWidget *label = gtk_label_new (caption);
GtkWidget *hbox = gtk_hbox_new (TRUE, 4);
gtk_container_add(GTK_CONTAINER (hbox), label);
gtk_container_add(GTK_CONTAINER (hbox), widget);
gtk_container_add(box, hbox);
}
void print_active(char * name, GtkToggleButton
*button)
{
gboolean active =
gtk_toggle_button_get_active(button);
printf("%s 는 현재 %s 상태입니다.\n", name, active? “활
성":“비활성");
}
void button_clicked(GtkWidget *button, gpointer data)
{
print_active(“체크버튼",
GTK_TOGGLE_BUTTON(checkbutton));
print_active(“토글버튼",
GTK_TOGGLE_BUTTON(togglebutton));
print_active(“라디오버튼1",
GTK_TOGGLE_BUTTON(radiobutton1));
print_active(“라디오버튼2",
GTK_TOGGLE_BUTTON(radiobutton2));
printf("\n");
}
int main (int argc, char *argv[])
{
GtkWidget *window;
GtkWidget *button;
GtkWidget *vbox;
gtk_init (&argc, &argv);
window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(window), “버튼
즈” );
gtk_window_set_default_size(GTK_WINDOW(window),
200, 200);
g_signal_connect ( GTK_OBJECT (window), “destroy”,
GTK_SIGNAL_FUNC (quit), NULL);
