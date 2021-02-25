#include "rqt_dyros_gui/rqt_dyros_gui.h"
#include <pluginlib/class_list_macros.h>
#include <QStringList>

namespace rqt_dyros_gui {

RqtDyrosPlugin::RqtDyrosPlugin()
  : rqt_gui_cpp::Plugin()
  , widget_(0)
{
  // Constructor is called first before initPlugin function, needless to say.

  // give QObjects reasonable names
  setObjectName("RqtDyrosPlugin");
}

void RqtDyrosPlugin::initPlugin(qt_gui_cpp::PluginContext& context)
{
  // access standalone command line arguments
  QStringList argv = context.argv();
  // create QWidget
  widget_ = new QWidget();
  // extend the widget with all attributes and children from UI file
  ui_.setupUi(widget_);
  // add widget to the user interface
  context.addWidget(widget_);

  mySub = nh_.subscribe("/subs",100,&RqtDyrosPlugin::subCallback, this);
  myPub = nh_.advertise<std_msgs::Float32>("/pubs",100);

  connect(ui_.myPushButton,SIGNAL(clicked()),this,SLOT(pushbutton()));
}

void RqtDyrosPlugin::pushbutton()
{
  myMsg.data++;
  myPub.publish(myMsg);
}
void RqtDyrosPlugin::subCallback(const std_msgs::Float32ConstPtr &msg)
{
  ui_.myLabel->setText(QString::number(msg->data));
}

void RqtDyrosPlugin::shutdownPlugin()
{
  // TODO unregister all publishers here
}

void RqtDyrosPlugin::saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const
{
  // TODO save intrinsic configuration, usually using:
  // instance_settings.setValue(k, v)
}

void RqtDyrosPlugin::restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings)
{
  // TODO restore intrinsic configuration, usually using:
  // v = instance_settings.value(k)
}

/*bool hasConfiguration() const
{
  return true;
}

void triggerConfiguration()
{
  // Usually used to open a dialog to offer the user a set of configuration
}*/

} // namespace

PLUGINLIB_EXPORT_CLASS(rqt_dyros_gui::RqtDyrosPlugin, rqt_gui_cpp::Plugin)