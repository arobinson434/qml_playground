#include <QAbstractListModel>

#include <iostream>

class TestData {
    public:
        TestData(QString name, int value): m_name(name), m_value(value) {}

        QString name() const     { return m_name;   }

        int     value() const    { return m_value;  }
        void setValue(int value) { m_value = value; }

    private:
        QString m_name;
        int     m_value;
};

class TestModel: public QAbstractListModel {
    Q_OBJECT
    public:
        enum AnimalRoles {
            NameRole = Qt::UserRole + 1,
            ValueRole
        };

        TestModel(QObject* parent=0): QAbstractListModel(parent) {
            addData("Bob", 42);
            addData("Jim", 73);
        }

        Q_INVOKABLE void addData(QString name, int value) {
            std::cout << "In addData()\n";

            beginInsertRows(QModelIndex(), rowCount(), rowCount());
            m_data << TestData(name, value);
            endInsertRows();
        }

        int rowCount(const QModelIndex& parent=QModelIndex()) const override {
            Q_UNUSED(parent);
            return m_data.count();
        }

        QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const override {
            std::cout << "data() - Index: " << index.row() << " Role: " << roleNames()[role].data();

            if ( index.row() >= 0 && index.row() < rowCount() ) {
                if ( role == NameRole ) {
                    std::cout << " Value: " << m_data[index.row()].name().toStdString() << std::endl;
                    return m_data[index.row()].name();
                } else if ( role == ValueRole ) {
                    std::cout << " Value: " << m_data[index.row()].value() << std::endl;
                    return m_data[index.row()].value();
                }
            }

            std::cout << std::endl;
            return QVariant();
        }

        Q_INVOKABLE bool setData(const QModelIndex& index, const QVariant& value, int role=Qt::EditRole) override {
            std::cout << "setData() - Index: " << index.row() << " Role: " << roleNames()[role].data();

            if ( index.row() >= 0 && index.row() < rowCount() ) {
                if ( role == ValueRole ) {
                    bool success = false;
                    int  new_val = value.toInt(&success);

                    if ( success ) {
                        std::cout << " Value: " << new_val << std::endl;

                        m_data[index.row()].setValue(new_val);
                        emit dataChanged(index, index, {ValueRole});

                        return true;
                    }
                }
            }

            std::cout << std::endl;
            return false;
        }

        Qt::ItemFlags flags(const QModelIndex& index) const override {
            return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
        }
    
    protected:
        QHash<int, QByteArray> roleNames() const override {
            return { {NameRole, "name"}, {ValueRole, "value"} };
        }

    private:
        QList<TestData> m_data;
};

class TestCtlr: public QObject {
    Q_OBJECT
    Q_PROPERTY(TestModel* model READ model CONSTANT)

    public:
        TestCtlr(QObject* parent=0): QObject(parent) {
            m_model = new TestModel(this);
        }

        TestModel* model() const { return m_model; }

    private:
        TestModel* m_model;
};

