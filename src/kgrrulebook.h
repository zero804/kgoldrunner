/****************************************************************************
 *    Copyright 2009  Ian Wadham <ianwau@gmail.com>                         *
 *                                                                          *
 *    This program is free software; you can redistribute it and/or         *
 *    modify it under the terms of the GNU General Public License as        *
 *    published by the Free Software Foundation; either version 2 of        *
 *    the License, or (at your option) any later version.                   *
 *                                                                          *
 *    This program is distributed in the hope that it will be useful,       *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *    GNU General Public License for more details.                          *
 *                                                                          *
 *    You should have received a copy of the GNU General Public License     *
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ****************************************************************************/

#ifndef KGRRULEBOOK_H
#define KGRRULEBOOK_H

#include <QObject>
#include <QList>
#include <QPoint>

#include <KDebug>

#include "kgrconsts.h" // OBSOLESCENT - 1/1/09
#include "kgrglobals.h"

class KGrLevelGrid;

class KGrRuleBook : public QObject
{
    Q_OBJECT
public:
    KGrRuleBook (QObject * parent);
    virtual ~KGrRuleBook();

    virtual void printRules() const = 0;

    bool alwaysCollectNugget() const { return mAlwaysCollectNugget; }
    bool runThruHole() const         { return mRunThruHole;         }
    bool reappearAtTop() const       { return mReappearAtTop;       }
    int  reappearRow() const         { return mReappearRow;         }
    int  pointsPerCell() const       { return mPointsPerCell;       }
    bool turnAnywhere() const        { return mTurnAnywhere;        }
    bool enemiesShowGold() const     { return mEnemiesShowGold;     }

    inline void getHeroTimes  (int & runTime, int & fallTime) {
                runTime = times.hwalk; fallTime = times.hfall; }
    inline void getEnemyTimes (int & runTime, int & fallTime, int & trapTime) {
                runTime = times.ewalk; fallTime = times.efall;
                trapTime = times.ecaptive; }
    inline void getDigTimes   (int & digTime, int & digCounter) {
                digTime = 200; digCounter = times.hole; }

    virtual Direction findBestWay (const QPoint & enemyPosition,
                                   const QPoint & heroPosition,
                                   const KGrLevelGrid & grid) = 0;

protected:
    bool mVariableTiming;	///< More enemies imply less speed.
    bool mAlwaysCollectNugget;	///< Enemies always collect nuggets.
    bool mRunThruHole;		///< Enemy can run L/R through dug hole.
    bool mReappearAtTop;	///< Enemies reborn at top of screen.
    int  mReappearRow;		///< Row where enemies reappear.
    int  mPointsPerCell;	///< Number of points in each grid-cell.
    bool mTurnAnywhere;		///< Can change direction anywhere in grid-cell.
    bool mEnemiesShowGold;	///< Enemies show when they are carrying gold.

    Timing times;
};


class KGrTraditionalRules : public KGrRuleBook
{
    Q_OBJECT
public:
    KGrTraditionalRules (QObject * parent);
    ~KGrTraditionalRules();

    void printRules() const { kDebug() << "Traditional rules." <<
                                 mVariableTiming << mAlwaysCollectNugget <<
                                 mRunThruHole << mReappearAtTop; }

    Direction findBestWay (const QPoint & enemyPosition,
                           const QPoint & heroPosition,
                           const KGrLevelGrid & grid);

private:
    void setTiming     (const int enemyCount = 0);
};


class KGrKGoldrunnerRules : public KGrRuleBook
{
    Q_OBJECT
public:
    KGrKGoldrunnerRules (QObject * parent);
    ~KGrKGoldrunnerRules();

    void printRules() const { kDebug() << "KGoldrunner rules." <<
                                 mVariableTiming << mAlwaysCollectNugget <<
                                 mRunThruHole << mReappearAtTop; }

    Direction findBestWay (const QPoint & enemyPosition,
                           const QPoint & heroPosition,
                           const KGrLevelGrid & grid);
};


class KGrScavengerRules : public KGrRuleBook
{
    Q_OBJECT
public:
    KGrScavengerRules (QObject * parent);
    ~KGrScavengerRules();

    void printRules() const { kDebug() << "Scavenger rules." <<
                                 mVariableTiming << mAlwaysCollectNugget <<
                                 mRunThruHole << mReappearAtTop; }

    Direction findBestWay (const QPoint & enemyPosition,
                           const QPoint & heroPosition,
                           const KGrLevelGrid & grid);
};

#endif // KGRRULEBOOK_H
