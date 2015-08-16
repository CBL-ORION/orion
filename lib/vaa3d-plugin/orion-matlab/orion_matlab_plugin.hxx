/* orion_matlab_plugin.hxx
 * This is a test plugin, you can use it as a demo. orion_matlab
 * 2015-6-10 : by orion_matlab
 */

#ifndef __ORION_MATLAB_PLUGIN_H__
#define __ORION_MATLAB_PLUGIN_H__

#include <QtGui>
#include <v3d_interface.h>

class ORION_MATLABTestPlugin : public QObject, public V3DPluginInterface2_1
{
	Q_OBJECT
	Q_INTERFACES(V3DPluginInterface2_1);

public:
	float getPluginVersion() const {return 1.1f;}

	QStringList menulist() const;
	void domenu(const QString &menu_name, V3DPluginCallback2 &callback, QWidget *parent);

	QStringList funclist() const ;
	bool dofunc(const QString &func_name, const V3DPluginArgList &input, V3DPluginArgList &output, V3DPluginCallback2 &callback, QWidget *parent);
};

#endif

