#include "Animal.hpp"

#include <QtCore/QAbstractListModel>
#include <QtCore/QStringList>

class AnimalModel : public QAbstractListModel
{
	Q_OBJECT
public:
	enum AnimalRoles
	{
		TypeRole = Qt::UserRole + 1,
		SizeRole,
		RealSizeRole
	};

	AnimalModel( QObject *parent = 0 );

	void addAnimal( const Animal &animal );

	int rowCount( const QModelIndex & parent = QModelIndex( ) ) const;

	QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const;

private:
	QList<Animal> m_animals;
};

