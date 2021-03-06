#ifndef CSV_DOC_VIEW_H
#define CSV_DOC_VIEW_H

#include <vector>
#include <map>

#include <QMainWindow>

#include "subviewfactory.hpp"

class QAction;
class QDockWidget;

namespace CSMDoc
{
    class Document;
}

namespace CSMWorld
{
    class UniversalId;
}

namespace CSVDoc
{
    class ViewManager;
    class Operations;
    class GlobalDebugProfileMenu;

    class View : public QMainWindow
    {
            Q_OBJECT

            ViewManager& mViewManager;
            CSMDoc::Document *mDocument;
            int mViewIndex;
            int mViewTotal;
            QList<SubView *> mSubViews;
            QAction *mUndo;
            QAction *mRedo;
            QAction *mSave;
            QAction *mVerify;
            QAction *mShowStatusBar;
            QAction *mStopDebug;
            std::vector<QAction *> mEditingActions;
            Operations *mOperations;
            SubViewFactoryManager mSubViewFactory;
            QMainWindow mSubViewWindow;
            GlobalDebugProfileMenu *mGlobalDebugProfileMenu;


            // not implemented
            View (const View&);
            View& operator= (const View&);

        private:

            void closeEvent (QCloseEvent *event);

            void setupFileMenu();

            void setupEditMenu();

            void setupViewMenu();

            void setupWorldMenu();

            void setupMechanicsMenu();

            void setupCharacterMenu();

            void setupAssetsMenu();

            void setupDebugMenu();

            void setupUi();

            void updateTitle(const std::string subview = "");

            void updateActions();

            void exitApplication();

            void loadUserSettings();

            /// User preference function
            void resizeViewWidth (int width);

            /// User preference function
            void resizeViewHeight (int height);

        public:

            View (ViewManager& viewManager, CSMDoc::Document *document, int totalViews);

            ///< The ownership of \a document is not transferred to *this.

            virtual ~View();

            const CSMDoc::Document *getDocument() const;

            CSMDoc::Document *getDocument();

            void setIndex (int viewIndex, int totalViews);

            void updateDocumentState();

            void updateProgress (int current, int max, int type, int threads);

            void toggleStatusBar(bool checked);

            Operations *getOperations() const;

            /// Function called by view manager when user preferences are updated
            void updateEditorSetting (const QString &, const QString &);

            // called when subviews are added or removed
            void updateSubViewIndicies(SubView *view = 0);

        signals:

            void newGameRequest();

            void newAddonRequest();

            void loadDocumentRequest();

            void exitApplicationRequest (CSVDoc::View *view);

            void editSettingsRequest();

        public slots:

            void addSubView (const CSMWorld::UniversalId& id, const std::string& hint = "");
            ///< \param hint Suggested view point (e.g. coordinates in a 3D scene or a line number
            /// in a script).

            void abortOperation (int type);

            void updateUserSetting (const QString &, const QStringList &);

        private slots:

            void newView();

            void save();

            void exit();

            void verify();

            void addGlobalsSubView();

            void addGmstsSubView();

            void addSkillsSubView();

            void addClassesSubView();

            void addFactionsSubView();

            void addRacesSubView();

            void addSoundsSubView();

            void addScriptsSubView();

            void addRegionsSubView();

            void addBirthsignsSubView();

            void addSpellsSubView();

            void addCellsSubView();

            void addReferenceablesSubView();

            void addReferencesSubView();

            void addRegionMapSubView();

            void addFiltersSubView();

            void addTopicsSubView();

            void addJournalsSubView();

            void addTopicInfosSubView();

            void addJournalInfosSubView();

            void addEnchantmentsSubView();

            void addBodyPartsSubView();

            void addSoundGensSubView();

            void addMagicEffectsSubView();

            void addMeshesSubView();

            void addIconsSubView();

            void addMusicsSubView();

            void addSoundsResSubView();

            void addTexturesSubView();

            void addVideosSubView();

            void addDebugProfilesSubView();

            void addRunLogSubView();

            void addPathgridSubView();

            void toggleShowStatusBar (bool show);

            void loadErrorLog();

            void run (const std::string& profile, const std::string& startupInstruction = "");

            void stop();
    };
}

#endif
