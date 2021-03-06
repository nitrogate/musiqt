/*
 *  Copyright (C) 2013-2021 Leandro Nini
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QWidget>

#include <algorithm>

class proxymodel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    enum class sortMode { Ascending, Descending, Random };

private:
    sortMode mode;

    QVector<int> m_randomOrder;

private:
    proxymodel() {}
    proxymodel(const proxymodel&);
    proxymodel& operator=(const proxymodel&);

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override
    {
        if (mode == sortMode::Random)
        {
            // NOTE cannot return random value as this function must be consistent
            // see https://bugs.kde.org/show_bug.cgi?id=413018
            // https://commits.kde.org/plasma-workspace/a1cf305ffb21b8ae8bbaf4d6ce03bbaa94cff405
            return m_randomOrder.indexOf(source_left.row()) < m_randomOrder.indexOf(source_right.row());
        }
        return QSortFilterProxyModel::lessThan(source_left, source_right);
    }

public:
    proxymodel(QWidget * parent) :
        QSortFilterProxyModel(parent),
        mode(sortMode::Ascending)
    {}

    void sort(sortMode newMode)
    {
        if ((mode == newMode) && (newMode != sortMode::Random))
            return;

        mode = newMode;

        QSortFilterProxyModel::sort(-1);

        Qt::SortOrder order;
        switch (mode)
        {
        case sortMode::Ascending:
            order = Qt::AscendingOrder;
            break;
        case sortMode::Descending:
            order = Qt::DescendingOrder;
            break;
        case sortMode::Random:
            order = Qt::AscendingOrder;
            m_randomOrder.resize(sourceModel()->rowCount());
            std::iota(m_randomOrder.begin(), m_randomOrder.end(), 0);
            std::random_shuffle(m_randomOrder.begin(), m_randomOrder.end());
            break;
        }

        QSortFilterProxyModel::sort(0, order);
    }

    sortMode getMode() const { return mode; }
};

#endif
