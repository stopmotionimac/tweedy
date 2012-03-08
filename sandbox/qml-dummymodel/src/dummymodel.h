
#ifndef DUMMYMODEL_H
#define DUMMYMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QStringList>

class DummyModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DummyRoles {
	TitleRole=Qt::UserRole+1
    };

    DummyModel(QObject* parent=NULL);
    ~DummyModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:

    void fillData();
    QStringList m_data;
};

#endif // DUMMYMODEL_H

