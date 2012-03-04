
#include "dummymodel.h"

#include <QtCore/QDateTime>

DummyModel::DummyModel(QObject *parent) : QAbstractListModel(parent)
{
    m_data.clear();
    QHash<int, QByteArray> roles;
    roles[TitleRole]="title";
    setRoleNames(roles);
    fillData();
}

DummyModel::~DummyModel()
{

}

int DummyModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant DummyModel::data(const QModelIndex &index, int role) const
{
    qDebug("dummymodel::data");
    qDebug("Role: %d", role);
    if (!index.isValid()) return QVariant();
    if ((index.row()<0) || (index.row()>=m_data.count())) return QVariant();
    if (role==TitleRole)
	return m_data.at(index.row());
    return QVariant();
}

void DummyModel::fillData()
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    beginResetModel();
    m_data.clear();
    int num=1+qrand()%8;
    for (int i=0; i<num; i++)
    {
	m_data.append(QString("DummyText%1").arg(i+1));
    }
    endResetModel();
}

bool DummyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug("SetData called");
    return true;
}

