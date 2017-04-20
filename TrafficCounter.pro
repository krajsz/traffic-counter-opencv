QT += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrafficCounter
TEMPLATE = app

CONFIG += C++11 thread
INCLUDEPATH+= 3rdparty

SOURCES += trafficCounterApp.cpp \
    src/backend/database/DatabaseManager.cpp \
    src/backend/CommandLineParser.cpp \
    src/backend/FrameProcessor.cpp \
    src/backend/TrafficCounterController.cpp \
    src/backend/Utils.cpp \
    src/backend/VehicleBlob.cpp \
    src/backend/VideoProcessor.cpp \
    src/backend/VideoRecorder.cpp \
    src/videosources/AbstractVideoSource.cpp \
    src/videosources/CameraVideoSource.cpp \
    src/videosources/FileVideoSource.cpp \
    src/videosources/LiveIPCameraVideoSource.cpp \
    src/widgets/CameraVideoSourceOptionsWidget.cpp \
    src/widgets/DatabaseSettingsDialog.cpp \
    src/widgets/FileInfoDialog.cpp \
    src/widgets/FileVideoSourceOptionsWidget.cpp \
    src/widgets/FileVideoSourceProgressBar.cpp \
    src/widgets/IPCameraVideoSourceOptionsWidget.cpp \
    src/widgets/PlaybackActionsDock.cpp \
    src/widgets/TrafficCounterMainWindow.cpp \
    src/widgets/VideoSourceDock.cpp \
    3rdparty/package_analysis/ForegroundMaskAnalysis.cpp \
    3rdparty/package_analysis/PerformanceUtils.cpp \
    3rdparty/package_analysis/PixelUtils.cpp \
    3rdparty/package_bgs/_template_/Amber.cpp \
    3rdparty/package_bgs/_template_/MyBGS.cpp \
    3rdparty/package_bgs/dp/AdaptiveMedianBGS.cpp \
    3rdparty/package_bgs/dp/Eigenbackground.cpp \
    3rdparty/package_bgs/dp/Error.cpp \
    3rdparty/package_bgs/dp/GrimsonGMM.cpp \
    3rdparty/package_bgs/dp/Image.cpp \
    3rdparty/package_bgs/dp/MeanBGS.cpp \
    3rdparty/package_bgs/dp/PratiMediodBGS.cpp \
    3rdparty/package_bgs/dp/TextureBGS.cpp \
    3rdparty/package_bgs/dp/WrenGA.cpp \
    3rdparty/package_bgs/dp/ZivkovicAGMM.cpp \
    3rdparty/package_bgs/IMBS/IMBS.cpp \
    3rdparty/package_bgs/KDE/KernelTable.cpp \
    3rdparty/package_bgs/KDE/NPBGmodel.cpp \
    3rdparty/package_bgs/KDE/NPBGSubtractor.cpp \
    3rdparty/package_bgs/lb/BGModel.cpp \
    3rdparty/package_bgs/lb/BGModelFuzzyGauss.cpp \
    3rdparty/package_bgs/lb/BGModelFuzzySom.cpp \
    3rdparty/package_bgs/lb/BGModelGauss.cpp \
    3rdparty/package_bgs/lb/BGModelMog.cpp \
    3rdparty/package_bgs/lb/BGModelSom.cpp \
    3rdparty/package_bgs/LBP_MRF/graph.cpp \
    3rdparty/package_bgs/LBP_MRF/maxflow.cpp \
    3rdparty/package_bgs/LBP_MRF/MEDefs.cpp \
    3rdparty/package_bgs/LBP_MRF/MEHistogram.cpp \
    3rdparty/package_bgs/LBP_MRF/MEImage.cpp \
    3rdparty/package_bgs/LBP_MRF/MotionDetection.cpp \
    3rdparty/package_bgs/LBSP/BackgroundSubtractorLBSP.cpp \
    3rdparty/package_bgs/LBSP/BackgroundSubtractorLBSP_.cpp \
    3rdparty/package_bgs/LBSP/BackgroundSubtractorLOBSTER.cpp \
    3rdparty/package_bgs/LBSP/BackgroundSubtractorPAWCS.cpp \
    3rdparty/package_bgs/LBSP/BackgroundSubtractorSuBSENSE.cpp \
    3rdparty/package_bgs/LBSP/LBSP.cpp \
    3rdparty/package_bgs/LBSP/LBSP_.cpp \
    3rdparty/package_bgs/MultiLayer/blob.cpp \
    3rdparty/package_bgs/MultiLayer/BlobExtraction.cpp \
    3rdparty/package_bgs/MultiLayer/BlobResult.cpp \
    3rdparty/package_bgs/MultiLayer/CMultiLayerBGS.cpp \
    3rdparty/package_bgs/MultiLayer/LocalBinaryPattern.cpp \
    3rdparty/package_bgs/PBAS/PBAS.cpp \
    3rdparty/package_bgs/SigmaDelta/sdLaMa091.cpp \
    3rdparty/package_bgs/T2F/FuzzyUtils.cpp \
    3rdparty/package_bgs/T2F/MRF.cpp \
    3rdparty/package_bgs/T2F/T2FGMM.cpp \
    3rdparty/package_bgs/T2F/T2FMRF.cpp \
    3rdparty/package_bgs/TwoPoints/two_points.cpp \
    3rdparty/package_bgs/ViBe/vibe-background-sequential.cpp \
    3rdparty/package_bgs/VuMeter/TBackground.cpp \
    3rdparty/package_bgs/VuMeter/TBackgroundVuMeter.cpp \
    3rdparty/package_bgs/AdaptiveBackgroundLearning.cpp \
    3rdparty/package_bgs/AdaptiveSelectiveBackgroundLearning.cpp \
    3rdparty/package_bgs/CodeBook.cpp \
    3rdparty/package_bgs/DPAdaptiveMedian.cpp \
    3rdparty/package_bgs/DPEigenbackground.cpp \
    3rdparty/package_bgs/DPGrimsonGMM.cpp \
    3rdparty/package_bgs/DPMean.cpp \
    3rdparty/package_bgs/DPPratiMediod.cpp \
    3rdparty/package_bgs/DPTexture.cpp \
    3rdparty/package_bgs/DPWrenGA.cpp \
    3rdparty/package_bgs/DPZivkovicAGMM.cpp \
    3rdparty/package_bgs/FrameDifference.cpp \
    3rdparty/package_bgs/FuzzyChoquetIntegral.cpp \
    3rdparty/package_bgs/FuzzySugenoIntegral.cpp \
    3rdparty/package_bgs/GMG.cpp \
    3rdparty/package_bgs/IndependentMultimodal.cpp \
    3rdparty/package_bgs/KDE.cpp \
    3rdparty/package_bgs/KNN.cpp \
    3rdparty/package_bgs/LBAdaptiveSOM.cpp \
    3rdparty/package_bgs/LBFuzzyAdaptiveSOM.cpp \
    3rdparty/package_bgs/LBFuzzyGaussian.cpp \
    3rdparty/package_bgs/LBMixtureOfGaussians.cpp \
    3rdparty/package_bgs/LBP_MRF.cpp \
    3rdparty/package_bgs/LBSimpleGaussian.cpp \
    3rdparty/package_bgs/LOBSTER.cpp \
    3rdparty/package_bgs/MixtureOfGaussianV1.cpp \
    3rdparty/package_bgs/MixtureOfGaussianV2.cpp \
    3rdparty/package_bgs/MultiCue.cpp \
    3rdparty/package_bgs/MultiLayer.cpp \
    3rdparty/package_bgs/PAWCS.cpp \
    3rdparty/package_bgs/PixelBasedAdaptiveSegmenter.cpp \
    3rdparty/package_bgs/SigmaDelta.cpp \
    3rdparty/package_bgs/StaticFrameDifference.cpp \
    3rdparty/package_bgs/SuBSENSE.cpp \
    3rdparty/package_bgs/T2FGMM_UM.cpp \
    3rdparty/package_bgs/T2FGMM_UV.cpp \
    3rdparty/package_bgs/T2FMRF_UM.cpp \
    3rdparty/package_bgs/T2FMRF_UV.cpp \
    3rdparty/package_bgs/TwoPoints.cpp \
    3rdparty/package_bgs/ViBe.cpp \
    3rdparty/package_bgs/VuMeter.cpp \
    3rdparty/package_bgs/WeightedMovingMean.cpp \
    3rdparty/package_bgs/WeightedMovingVariance.cpp \
    3rdparty/package_bgs/_template_/amber/amber.c

HEADERS  += src/backend/database/DatabaseManager.h \
    src/backend/CommandLineParser.h \
    src/backend/FrameProcessor.h \
    src/backend/TrafficCounterController.h \
    src/backend/Utils.h \
    src/backend/VehicleBlob.h \
    src/backend/VideoProcessor.h \
    src/backend/VideoRecorder.h \
    src/videosources/AbstractVideoSource.h \
    src/videosources/CameraVideoSource.h \
    src/videosources/FileVideoSource.h \
    src/videosources/LiveIPCameraVideoSource.h \
    src/widgets/CameraVideoSourceOptionsWidget.h \
    src/widgets/DatabaseSettingsDialog.h \
    src/widgets/FileInfoDialog.h \
    src/widgets/FileVideoSourceOptionsWidget.h \
    src/widgets/FileVideoSourceProgressBar.h \
    src/widgets/IPCameraVideoSourceOptionsWidget.h \
    src/widgets/PlaybackActionsDock.h \
    src/widgets/TrafficCounterMainWindow.h \
    src/widgets/VideoSourceDock.h \
    3rdparty/package_analysis/ForegroundMaskAnalysis.h \
    3rdparty/package_analysis/PerformanceUtils.h \
    3rdparty/package_analysis/PixelUtils.h \
    3rdparty/package_bgs/_template_/amber/amber.h \
    3rdparty/package_bgs/_template_/Amber.h \
    3rdparty/package_bgs/_template_/MyBGS.h \
    3rdparty/package_bgs/dp/AdaptiveMedianBGS.h \
    3rdparty/package_bgs/dp/Bgs.h \
    3rdparty/package_bgs/dp/BgsParams.h \
    3rdparty/package_bgs/dp/Eigenbackground.h \
    3rdparty/package_bgs/dp/Error.h \
    3rdparty/package_bgs/dp/GrimsonGMM.h \
    3rdparty/package_bgs/dp/Image.h \
    3rdparty/package_bgs/dp/MeanBGS.h \
    3rdparty/package_bgs/dp/PratiMediodBGS.h \
    3rdparty/package_bgs/dp/TextureBGS.h \
    3rdparty/package_bgs/dp/WrenGA.h \
    3rdparty/package_bgs/dp/ZivkovicAGMM.h \
    3rdparty/package_bgs/IMBS/IMBS.hpp \
    3rdparty/package_bgs/KDE/KernelTable.h \
    3rdparty/package_bgs/KDE/NPBGmodel.h \
    3rdparty/package_bgs/KDE/NPBGSubtractor.h \
    3rdparty/package_bgs/lb/BGModel.h \
    3rdparty/package_bgs/lb/BGModelFuzzyGauss.h \
    3rdparty/package_bgs/lb/BGModelFuzzySom.h \
    3rdparty/package_bgs/lb/BGModelGauss.h \
    3rdparty/package_bgs/lb/BGModelMog.h \
    3rdparty/package_bgs/lb/BGModelSom.h \
    3rdparty/package_bgs/lb/Types.h \
    3rdparty/package_bgs/LBP_MRF/block.h \
    3rdparty/package_bgs/LBP_MRF/graph.h \
    3rdparty/package_bgs/LBP_MRF/MEDefs.hpp \
    3rdparty/package_bgs/LBP_MRF/MEHistogram.hpp \
    3rdparty/package_bgs/LBP_MRF/MEImage.hpp \
    3rdparty/package_bgs/LBP_MRF/MotionDetection.hpp \
    3rdparty/package_bgs/LBSP/BackgroundSubtractorLBSP.h \
    3rdparty/package_bgs/LBSP/BackgroundSubtractorLBSP_.h \
    3rdparty/package_bgs/LBSP/BackgroundSubtractorLOBSTER.h \
    3rdparty/package_bgs/LBSP/BackgroundSubtractorPAWCS.h \
    3rdparty/package_bgs/LBSP/BackgroundSubtractorSuBSENSE.h \
    3rdparty/package_bgs/LBSP/DistanceUtils.h \
    3rdparty/package_bgs/LBSP/LBSP.h \
    3rdparty/package_bgs/LBSP/LBSP_.h \
    3rdparty/package_bgs/LBSP/RandUtils.h \
    3rdparty/package_bgs/MultiLayer/BackgroundSubtractionAPI.h \
    3rdparty/package_bgs/MultiLayer/BGS.h \
    3rdparty/package_bgs/MultiLayer/blob.h \
    3rdparty/package_bgs/MultiLayer/BlobExtraction.h \
    3rdparty/package_bgs/MultiLayer/BlobLibraryConfiguration.h \
    3rdparty/package_bgs/MultiLayer/BlobResult.h \
    3rdparty/package_bgs/MultiLayer/CMultiLayerBGS.h \
    3rdparty/package_bgs/MultiLayer/LocalBinaryPattern.h \
    3rdparty/package_bgs/MultiLayer/OpenCvDataConversion.h \
    3rdparty/package_bgs/MultiLayer/OpenCvLegacyIncludes.h \
    3rdparty/package_bgs/PBAS/PBAS.h \
    3rdparty/package_bgs/SigmaDelta/sdLaMa091.h \
    3rdparty/package_bgs/T2F/FuzzyUtils.h \
    3rdparty/package_bgs/T2F/MRF.h \
    3rdparty/package_bgs/T2F/T2FGMM.h \
    3rdparty/package_bgs/T2F/T2FMRF.h \
    3rdparty/package_bgs/TwoPoints/two_points.h \
    3rdparty/package_bgs/ViBe/vibe-background-sequential.h \
    3rdparty/package_bgs/VuMeter/TBackground.h \
    3rdparty/package_bgs/VuMeter/TBackgroundVuMeter.h \
    3rdparty/package_bgs/AdaptiveBackgroundLearning.h \
    3rdparty/package_bgs/AdaptiveSelectiveBackgroundLearning.h \
    3rdparty/package_bgs/bgslibrary.h \
    3rdparty/package_bgs/CodeBook.h \
    3rdparty/package_bgs/DPAdaptiveMedian.h \
    3rdparty/package_bgs/DPEigenbackground.h \
    3rdparty/package_bgs/DPGrimsonGMM.h \
    3rdparty/package_bgs/DPMean.h \
    3rdparty/package_bgs/DPPratiMediod.h \
    3rdparty/package_bgs/DPTexture.h \
    3rdparty/package_bgs/DPWrenGA.h \
    3rdparty/package_bgs/DPZivkovicAGMM.h \
    3rdparty/package_bgs/FrameDifference.h \
    3rdparty/package_bgs/FuzzyChoquetIntegral.h \
    3rdparty/package_bgs/FuzzySugenoIntegral.h \
    3rdparty/package_bgs/GMG.h \
    3rdparty/package_bgs/IBGS.h \
    3rdparty/package_bgs/IndependentMultimodal.h \
    3rdparty/package_bgs/KDE.h \
    3rdparty/package_bgs/KNN.h \
    3rdparty/package_bgs/LBAdaptiveSOM.h \
    3rdparty/package_bgs/LBFuzzyAdaptiveSOM.h \
    3rdparty/package_bgs/LBFuzzyGaussian.h \
    3rdparty/package_bgs/LBMixtureOfGaussians.h \
    3rdparty/package_bgs/LBP_MRF.h \
    3rdparty/package_bgs/LBSimpleGaussian.h \
    3rdparty/package_bgs/LOBSTER.h \
    3rdparty/package_bgs/MixtureOfGaussianV1.h \
    3rdparty/package_bgs/MixtureOfGaussianV2.h \
    3rdparty/package_bgs/MultiCue.h \
    3rdparty/package_bgs/MultiLayer.h \
    3rdparty/package_bgs/PAWCS.h \
    3rdparty/package_bgs/PixelBasedAdaptiveSegmenter.h \
    3rdparty/package_bgs/SigmaDelta.h \
    3rdparty/package_bgs/StaticFrameDifference.h \
    3rdparty/package_bgs/SuBSENSE.h \
    3rdparty/package_bgs/T2FGMM_UM.h \
    3rdparty/package_bgs/T2FGMM_UV.h \
    3rdparty/package_bgs/T2FMRF_UM.h \
    3rdparty/package_bgs/T2FMRF_UV.h \
    3rdparty/package_bgs/TwoPoints.h \
    3rdparty/package_bgs/ViBe.h \
    3rdparty/package_bgs/VuMeter.h \
    3rdparty/package_bgs/WeightedMovingMean.h \
    3rdparty/package_bgs/WeightedMovingVariance.h

FORMS    += src/ui/cameravideosourceoptionswidget.ui \
    src/ui/databasesettingsdialog.ui \
    src/ui/fileinfodialog.ui \
    src/ui/filevideosourceoptionswidget.ui \
    src/ui/ipcameravideosourceoptions.ui \
    src/ui/playbackactionsdock.ui \
    src/ui/trafficcountermainwindow.ui \
    src/ui/videosourcedock.ui
LIBS += `pkg-config opencv --libs --cflags`

DISTFILES += \
    README.md \
    INSTALL \
    LICENSE \
    3rdparty/package_bgs/LBSP/LBSP_16bits_dbcross_1ch.i \
    3rdparty/package_bgs/LBSP/LBSP_16bits_dbcross_3ch1t.i \
    3rdparty/package_bgs/LBSP/LBSP_16bits_dbcross_3ch3t.i \
    3rdparty/package_bgs/LBSP/LBSP_16bits_dbcross_s3ch.i \
    3rdparty/package_bgs/ViBe/LICENSE

RESOURCES += \
    resources.qrc

