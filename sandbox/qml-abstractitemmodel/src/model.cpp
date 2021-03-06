
#include "model.h"

 AnimalModel::AnimalModel(QObject *parent)
     : QAbstractListModel(parent)
 {
     QHash<int, QByteArray> roles;
     roles[TypeRole] = "type";
     roles[SizeRole] = "size";
     roles[RealSizeRole] = "realSize";
     setRoleNames(roles);
 }

 void AnimalModel::addAnimal(const Animal &animal)
 {
     beginInsertRows(QModelIndex(), rowCount(), rowCount());
     m_animals << animal;
     endInsertRows();
 }

 int AnimalModel::rowCount(const QModelIndex & parent) const {
     return m_animals.count();
 }

 QVariant AnimalModel::data(const QModelIndex & index, int role) const {
     if (index.row() < 0 || index.row() > m_animals.count())
         return QVariant();

     const Animal &animal = m_animals[index.row()];
     if (role == TypeRole)
         return animal.type();
     else if (role == SizeRole)
         return animal.size();
	 else if (role == RealSizeRole)
         return animal.realSize();
     return QVariant();
 }

