#include "vtkSmartPointer.h"

#include "vtkRenderWindow.h"

#include "vtkRenderer.h"

#include "vtkRenderWindowInteractor.h"

#include "vtkInteractorStyleTrackballCamera.h"

#include "vtkCylinderSource.h"

#include "vtkPolyDataMapper.h"

#include "vtkActor.h"

#include "vtkProperty.h"

#include "vtkBMPReader.h"

#include "vtkImageFlip.h"

#include "vtkLight.h"

#include "vtkCamera.h"

#include "vtkPolyDataWriter.h"

#include "vtkOBJExporter.h"

#include "vtkArrowSource.h"

#include "vtkStructuredPointsReader.h"

#include "vtkHedgeHog.h"

#include "vtkLookupTable.h"

#include "vtkGlyph3D.h"

#include "vtkSphereSource.h"

#include "vtkConeSource.h"

#include "vtkPointData.h"

#include "vtkCubeSource.h"

#include "vtkDICOMImageReader.h"

#include "vtkImageShiftScale.h"

#include "vtkVolumeRayCastCompositeFunction.h"

#include "vtkGPUVolumeRayCastMapper.h"

#include "vtkColorTransferFunction.h"

#include "vtkPiecewiseFunction.h"

#include "vtkVolumeProperty.h"

#include "vtkMultiBlockDataSet.h"

#include "vtkMultiBlockDataSet.h"

#include "vtkImageShrink3D.h"

#include "vtkContourFilter.h"

#include "vtkDecimatePro.h"

#include "vtkSmoothPolyDataFilter.h"

#include "vtkPolyDataNormals.h"

#include "vtkStripper.h"

#include "vtkMaskPoints.h"

#include "vtkPolyDataReader.h"

#include "vtkCoordinate.h"

#include <iostream>

#include "vtkLookupTable.h"

#include "vtkExtractEdges.h"
#include "vtkTubeFilter.h"

#include "vtkGradientFilter.h"

#include "vtkAssignAttribute.h"

#include "vtkImageGradient.h"

#include "vtkVolume16Reader.h"
#include "vtkDataArray.h"
#include "vtkImageDataGeometryFilter.h"
#include "vtkTriangleFilter.h"
#include "vtkImageViewer.h"
#include "vtkVolumeRayCastMapper.h"
#include "vtkUnsignedCharArray.h"
#include "vtkRungeKutta4.h"
#include "vtkStreamTracer.h"
#include "vtkTubeFilter.h"
#include "vtkDataObject.h"
#include "vtkStructuredGridReader.h"
#include "vtkDataSetMapper.h"
#include "vtkStructuredGridWriter.h"
#include "vtkStructuredGrid.h"
#include "vtkPoints.h"

//itk头文件


#include "itkImage.h"
#include "itkImportImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageToVTKImageFilter.h"
#include <itkGDCMImageIO.h>    //此处使用尖括号更好
#include "itkMetaDataDictionary.h"
#include "itkMetaDataObject.h"
#include "itkGDCMImageIOFactory.h"

#include "itkGDCMSeriesFileNames.h"
#include "itkImageSeriesReader.h"
#include "itkConnectedThresholdImageFilter.h"//区域生长算法
#include "itkCurvatureFlowImageFilter.h"//图像中存在的噪声将大大降低滤波器生长大面积区域的能力。当面对噪声图像时，通常是使用一个边缘保留平滑滤波器
#include "itkindex.h"
#include "itkCastImageFilter.h"
#include "itkFlipImageFilter.h"//图片翻转
#include "itkSigmoidImageFilter.h"
#include "itkGradientMagnitudeImageFilter.h"
#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"
#include "itkDerivativeImageFilter.h"
#include "itkRecursiveGaussianImageFilter.h"
#include "itkAddImageFilter.h"
#include "itkLaplacianRecursiveGaussianImageFilter.h"
#include "itkMeanImageFilter.h"
#include "itkMedianImageFilter.h"
#include "itkBinaryErodeImageFilter.h"
#include "itkBinaryDilateImageFilter.h"
#include "itkBinaryBallStructuringElement.h"
#include "itkThresholdImageFilter.h"
#include "itkBinaryThresholdImageFilter.h"

//#include "vtkCallbackReaderProgress.h"


using namespace std;

//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
/*
int main()
{
vtkRenderer *renderer = vtkRenderer::New();
vtkRenderWindow *renWin = vtkRenderWindow::New();
renWin->AddRenderer(renderer);
vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
iren->SetRenderWindow(renWin);

//球体
vtkSphereSource *sphere = vtkSphereSource::New();
sphere->SetThetaResolution(8);   //设置球体在经度上的精度
sphere->SetPhiResolution(8); //设置球体在纬度上的精度

vtkPolyDataMapper *sphereMapper = vtkPolyDataMapper::New();
sphereMapper->SetInputConnection(sphere->GetOutputPort());//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!不能用setinputdata！！！！！！！！！！！！！！！！！！！！！！！！！！！！
vtkActor *sphereActor = vtkActor::New();
sphereActor->SetMapper(sphereMapper);

//圆锥体
vtkConeSource *cone = vtkConeSource::New();
cone->SetResolution(6);

//创建glyph对象
vtkGlyph3D *glyph = vtkGlyph3D::New();
glyph->SetInputData(sphere->GetOutput()); //设置输入集
glyph->SetSourceData(cone->GetOutput());  //设置对象源
glyph->SetVectorModeToUseNormal();       //设置方向
glyph->SetScaleModeToScaleByVector();    //设置伸缩模式
glyph->SetScaleFactor(0.25);         //设置伸缩比例

vtkPolyDataMapper *spikeMapper = vtkPolyDataMapper::New();
spikeMapper->SetInputConnection(glyph->GetOutputPort());

vtkActor *spikeActor = vtkActor::New();
spikeActor->SetMapper(spikeMapper);

renderer->AddActor(sphereActor);
//renderer->AddActor(spikeActor);
renderer->SetBackground(0.1, 0.2,0.4);
renWin->SetSize(300, 300);


renWin->AddRenderer(renderer);
vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =
vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
iren->SetInteractorStyle(style);



iren->Initialize();
// interact with data

iren->Start();
// Clean up
renderer->Delete();
renWin->Delete();
iren->Delete();
sphere->Delete();
sphereMapper->Delete();
sphereActor->Delete();
cone->Delete();
glyph->Delete();
spikeMapper->Delete();
spikeActor->Delete();

return 0;
}
*/

/*
int   main()
{
//读取结构化的网格数据文件

vtkSmartPointer<vtkStructuredPointsReader> pStructGrid = vtkStructuredPointsReader::New();

pStructGrid->SetFileName("test.vtk");

pStructGrid->Update();

//创建矢量数据的方向线

vtkSmartPointer<vtkHedgeHog> pHedHog = vtkHedgeHog::New();

pHedHog->SetInputData((vtkDataObject *)pStructGrid->GetOutput());

//设置缩放因子，控制方向线的长度

pHedHog->SetScaleFactor(0.3);

//颜色表

vtkSmartPointer<vtkLookupTable> pLookTable = vtkLookupTable::New();

pLookTable->Build();

//pLookTable->SetHueRange(0.667,0);

//创建映射器

vtkSmartPointer<vtkPolyDataMapper> pMapper = vtkPolyDataMapper::New();

pMapper->SetInputData(pHedHog->GetOutput());

pMapper->SetLookupTable(pLookTable);

//确定用颜色标识矢量数据标量值大小的范围

pMapper->SetScalarRange(50, 550);

pMapper->SetScalarVisibility(1);

vtkSmartPointer<vtkActor> pActor = vtkActor::New();

pActor->SetMapper(pMapper);

//绘制

vtkSmartPointer<vtkRenderer> renderer = vtkRenderer::New();

vtkSmartPointer<vtkRenderWindow> renWin = vtkRenderWindow::New();

renWin->AddRenderer(renderer);



vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkRenderWindowInteractor::New();

iren->SetRenderWindow(renWin);

renderer->AddActor(pActor);

renderer->ResetCamera();

renderer->SetBackground(1, 1, 1);

renWin->SetSize(300, 300);

renWin->Render();

iren->Start();

return 0;
}
*/
/**********************************贴图obj************************************/
/*
int main()
{
//图片读取
vtkSmartPointer<vtkBMPReader>bmpReader = vtkSmartPointer<vtkBMPReader>::New();

bmpReader->SetFileName("E:\\NEW\\a2.jpg");
//图片旋转(failed)
vtkSmartPointer<vtkImageFlip>imageFlip = vtkSmartPointer<vtkImageFlip>::New();
// 	imageFlip->SetInputConnection(bmpReader->GetOutputPort());
// 	imageFlip->SetFilteredAxes(2);
// 	imageFlip->Update();

//贴图
vtkSmartPointer<vtkTexture>texture = vtkSmartPointer<vtkTexture>::New();

texture->SetInputConnection(bmpReader->GetOutputPort());

texture->InterpolateOn();
//箭头
vtkSmartPointer<vtkArrowSource> arrowSource =
vtkSmartPointer<vtkArrowSource>::New();
arrowSource->SetShaftRadius(0.03);
arrowSource->SetTipLength(0.35);

arrowSource->Update();

//生成一个中心在渲染场景原点的柱体
vtkSmartPointer<vtkCylinderSource> cylinder =

vtkSmartPointer<vtkCylinderSource>::New();

cylinder->SetHeight(2.0);

cylinder->SetRadius(1.0);

cylinder->SetResolution(10);

//渲染多边形几何数据
vtkSmartPointer<vtkPolyDataMapper> cylinderMapper =

vtkSmartPointer<vtkPolyDataMapper>::New();

//	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());
//渲染场景中的数据的可视化表达
vtkSmartPointer<vtkActor> cylinderActor =

vtkSmartPointer<vtkActor>::New();
vtkSmartPointer<vtkPolyDataMapper> mymapper =

vtkSmartPointer<vtkPolyDataMapper>::New();
mymapper->SetInputConnection(cylinder->GetOutputPort());

vtkSmartPointer<vtkActor> myactor =

vtkSmartPointer<vtkActor>::New();

myactor->SetMapper(mymapper);

cylinderActor->GetProperty()->SetColor(1.0, 0, 0);
//	cylinderActor->SetMapper(cylinderMapper);
//cylinderActor->SetMapper(arrowSource);
//	cylinderActor->SetTexture(texture);

vtkSmartPointer<vtkGlyph3D> glyph = vtkGlyph3D::New();
glyph->SetInputData(cylinder->GetOutput());
glyph->SetSourceData(arrowSource->GetOutput());
glyph->SetVectorModeToUseNormal();
//	glyph->SetScaleModeToScaleByVector();
//	glyph->SetVectorModeToUseVector();
//glyph->SetColorModeToColorByVector();
glyph->SetScaleFactor(0.25);
glyph->SetColorMode(0);

cylinderMapper->SetInputConnection(glyph->GetOutputPort());
cylinderActor->SetMapper(cylinderMapper);

//负责管理场景的渲染过程
vtkSmartPointer<vtkRenderer> renderer =

vtkSmartPointer<vtkRenderer>::New();
renderer->AddActor(myactor);
renderer->AddActor(cylinderActor);

renderer->SetBackground(0.1, 0.2, 0.4);
renderer->SetViewport(0, 0, 0.5, 0.5);
//renderer->SetViewport(0.5, 0, 1, 0.5);
//renderer->SetViewport( 0.5, 0.5,0.5,1);
//renderer->SetViewport( 0.5, 0.5,1,1);

//将操作系统和vtk渲染引擎连接在一起
vtkSmartPointer<vtkRenderWindow> renWin =

vtkSmartPointer<vtkRenderWindow>::New();

renWin->AddRenderer(renderer);

renWin->SetSize(300, 300);
//提供独立的响应事件
vtkSmartPointer<vtkRenderWindowInteractor> iren =

vtkSmartPointer<vtkRenderWindowInteractor>::New();

iren->SetRenderWindow(renWin);

//交互器样式的一种，通过控制相机对物体操作
vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =

vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

iren->SetInteractorStyle(style);


// 	vtkSmartPointer<vtkPolyDataWriter> vtkWriter = vtkSmartPointer<vtkPolyDataWriter>::New();
// 	vtkWriter->SetInputData(cylinder->GetOutput());
// 	vtkWriter->SetFileName("test.vtk");
// 	vtkWriter->Write();

iren->Initialize();

iren->Start();
// 	vtkSmartPointer<vtkOBJExporter> porter = vtkSmartPointer<vtkOBJExporter>::New();
// 	porter->SetFilePrefix("E:\\outputstl\\qiuti");
// 	porter->SetInput(renWin);
// 	porter->Write();

std::cout << "end" << endl;
return 0;

}
*/
/*
int main()
{
// Create points
vtkSmartPointer<vtkPoints> points =
vtkSmartPointer<vtkPoints>::New();
points->InsertNextPoint(0, 0, 0);
points->InsertNextPoint(5, 0, 0);
points->InsertNextPoint(10, 0, 0);

// Setup scales. This can also be an Int array
// char is used since it takes the least memory
vtkSmartPointer<vtkUnsignedCharArray> colors =
vtkSmartPointer<vtkUnsignedCharArray>::New();
colors->SetName("colors");
colors->SetNumberOfComponents(3);
unsigned char r[3] = { 255, 0, 0 };
unsigned char g[3] = { 0, 255, 0 };
unsigned char b[3] = { 0, 0, 255 };
colors->InsertNextTupleValue(r);
colors->InsertNextTupleValue(g);
colors->InsertNextTupleValue(b);

// Combine into a polydata
vtkSmartPointer<vtkPolyData> polydata =
vtkSmartPointer<vtkPolyData>::New();
polydata->SetPoints(points);
polydata->GetPointData()->SetScalars(colors);

// Create anything you want here, we will use a cube for the demo.
vtkSmartPointer<vtkCubeSource> cubeSource =
vtkSmartPointer<vtkCubeSource>::New();
vtkSmartPointer<vtkArrowSource> m_arrow = vtkArrowSource::New();


vtkSmartPointer<vtkGlyph3D> glyph3D =
vtkSmartPointer<vtkGlyph3D>::New();
//glyph3D->SetColorModeToColorByScalar();
glyph3D->SetSourceConnection(m_arrow->GetOutputPort());
#if VTK_MAJOR_VERSION <= 5
glyph3D->SetInput(polydata);
#else
glyph3D->SetInputData(polydata);
#endif
glyph3D->ScalingOff();
glyph3D->Update();

// Create a mapper and actor
vtkSmartPointer<vtkPolyDataMapper> mapper =
vtkSmartPointer<vtkPolyDataMapper>::New();
mapper->SetInputConnection(glyph3D->GetOutputPort());
vtkSmartPointer<vtkActor> actor =
vtkSmartPointer<vtkActor>::New();
actor->SetMapper(mapper);

// Visualize
vtkSmartPointer<vtkRenderer> renderer =
vtkSmartPointer<vtkRenderer>::New();
vtkSmartPointer<vtkRenderWindow> renderWindow =
vtkSmartPointer<vtkRenderWindow>::New();
renderWindow->AddRenderer(renderer);
vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
vtkSmartPointer<vtkRenderWindowInteractor>::New();
renderWindowInteractor->SetRenderWindow(renderWindow);

renderer->AddActor(actor);
renderer->SetBackground(1, 1, 1); // Background color white

renderWindow->Render();
renderWindowInteractor->Start();

return EXIT_SUCCESS;

}
*/
#include <vtkSmartPointer.h>
#include <vtkPolygon.h>
#include <vtkTriangle.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkLookupTable.h>
#include <vtkTransformTextureCoords.h>

#include "vtkFloatArray.h"
/*
int main()
{
vtkSmartPointer<vtkPolyDataWriter> my_writer = vtkSmartPointer<vtkPolyDataWriter>::New();
vtkSmartPointer< vtkDICOMImageReader > reader = vtkSmartPointer< vtkDICOMImageReader >::New();
//reader->SetDirectoryName("E:\\Release\\LHYSE9");
reader->SetDirectoryName("E:\\SE00");
reader->SetDataScalarTypeToUnsignedShort();
reader->SetDataSpacing(0.5, 0.5, 1);
reader->SetDataByteOrderToLittleEndian();

// 	vtkSmartPointer<vtkContourFilter> skinExtractor =
// 		vtkSmartPointer<vtkContourFilter>::New();
// 	skinExtractor->SetInputConnection(reader->GetOutputPort());
//
// 	my_writer->SetInputConnection(skinExtractor->GetOutputPort());
// 	my_writer->SetFileName("E:\\121.vtk");
// 	my_writer->Write();

vtkImageShiftScale *shiftScale = vtkImageShiftScale::New();
shiftScale->SetInputConnection(reader->GetOutputPort());
shiftScale->SetOutputScalarTypeToUnsignedChar();

//	vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();

vtkSmartPointer<vtkImageShrink3D> m_shrink = vtkSmartPointer<vtkImageShrink3D>::New();//二次抽样

m_shrink->SetShrinkFactors(0, 0, 0);//调节绘制图像的精细程度
m_shrink->AveragingOn();
m_shrink->SetInputConnection(reader->GetOutputPort());

vtkSmartPointer<vtkContourFilter> m_skinExtractor = vtkSmartPointer<vtkContourFilter>::New();//生成等值面/线

m_skinExtractor->SetInputConnection(m_shrink->GetOutputPort());
m_skinExtractor->SetValue(0, 400);//调整阈值，400以上是骨组织
//	m_skinExtractor->SetValue(1, 800);//调整阈值，400以上是骨组织

vtkSmartPointer<vtkDecimatePro> m_deci = vtkSmartPointer<vtkDecimatePro>::New();//减少网格中三角形的数量

m_deci->SetTargetReduction(0.3);//减少到70%
m_deci->SetInputConnection(m_skinExtractor->GetOutputPort());

vtkSmartPointer<vtkSmoothPolyDataFilter> m_smooth = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();//拉普拉斯平滑

m_smooth->SetInputConnection(m_deci->GetOutputPort());
m_smooth->SetNumberOfIterations(200);

vtkSmartPointer<vtkPolyDataNormals> m_skinNormals = vtkSmartPointer<vtkPolyDataNormals>::New();//计算多边形网格的法线

m_skinNormals->SetInputConnection(m_smooth->GetOutputPort());
m_skinNormals->SetComputeCellNormals(1);
m_skinNormals->SetComputePointNormals(1);
m_skinNormals->SetFeatureAngle(60.0);//设置定义的锐角
//	m_skinNormals->Update();

vtkSmartPointer<vtkStripper> m_stripper = vtkSmartPointer<vtkStripper>::New();//创造三角形条

m_stripper->SetInputConnection(m_skinNormals->GetOutputPort());

vtkSmartPointer<vtkPolyData> m_poly = vtkSmartPointer<vtkPolyData>::New();


// 	vtkSmartPointer<vtkGradientFilter> grad11 =
// 		vtkSmartPointer<vtkGradientFilter>::New();
//
//
// 	//grad11->SetDimensionality(3);
// 	grad11->SetInputConnection(m_stripper->GetOutputPort());
// 	my_writer->SetInputConnection(grad11->GetOutputPort());
// 	my_writer->SetFileName("E:\\1221.vtk");
// 	my_writer->Write();
// 	system("pause");


vtkSmartPointer<vtkMaskPoints> mask =
vtkSmartPointer<vtkMaskPoints>::New();
mask->SetInputConnection(m_stripper->GetOutputPort());
mask->SetMaximumNumberOfPoints(300);
mask->RandomModeOn();

vtkSmartPointer<vtkCylinderSource> cylinder =

vtkSmartPointer<vtkCylinderSource>::New();

cylinder->SetHeight(2.0);

cylinder->SetRadius(1.0);

cylinder->SetResolution(10);

//cylinder->Update();

vtkSmartPointer<vtkArrowSource> m_arrow = vtkSmartPointer<vtkArrowSource>::New();
m_arrow->SetShaftRadius(0.03);
m_arrow->SetTipLength(0.35);

//m_arrow->Update();

vtkSmartPointer<vtkConeSource> m_cone = vtkSmartPointer<vtkConeSource>::New();
m_cone->SetHeight(3);
m_cone->SetRadius(1);
m_cone->SetResolution(10);

int i;
//定义立方体的顶点坐标
static float x[8][3] = { { 0, 0, 0 }, { 1, 0, 0 }, { 1, 1, 0 }, { 0, 1, 0 }, { 0, 0, 1 }, { 1, 0, 1 }, { 1, 1, 1 }, { 0, 1, 1 } };
//定义单元，每4个顶点建立一个四边形单元，共计6个单元
static vtkIdType pts[6][4] = { { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 0, 1, 5, 4 }, { 1, 2, 6, 5 }, { 2, 3, 7, 6 }, { 3, 0, 4, 7 } };
//创建对象
vtkPolyData *cube = vtkPolyData::New();
vtkPoints *points = vtkPoints::New();
vtkCellArray *polys = vtkCellArray::New();
//存储标量值
vtkFloatArray *scalars = vtkFloatArray::New();
//存储顶点
for (i = 0; i < 8; i++)points->InsertPoint(i, x[i]);
//设定单元
for (i = 0; i < 6; i++)polys->InsertNextCell(4, pts[i]);
//设定每个顶点的标量值
for (i = 0; i < 8; i++)scalars->InsertTuple1(i, i);
//创建多边形数据
cube->SetPoints(points);
//设定单元类型为多边形
cube->SetPolys(polys);
//设定每个顶点的标量值
//cube->GetPointData()->SetScalars(scalars);

unsigned char red[3] = { 255, 0, 0 };
unsigned char blue[3] = {0, 255, 0 };
unsigned char green[3] = { 0, 0, 255 };

vtkSmartPointer<vtkUnsignedCharArray> m_point = vtkSmartPointer<vtkUnsignedCharArray>::New();

m_point->SetNumberOfComponents(3);
m_point->InsertNextTypedTuple(red);
m_point->InsertNextTypedTuple(green);
m_point->InsertNextTypedTuple(blue);
m_point->InsertNextTypedTuple(green);
m_point->InsertNextTypedTuple(blue);

vtkSmartPointer<vtkPointData> ppdd = vtkSmartPointer<vtkPointData>::New();


ppdd =  m_cone->GetOutput()->GetPointData();
int qqqqq = ppdd->GetNumberOfArrays();

vtkSmartPointer<vtkGlyph3D> glyph =
vtkSmartPointer<vtkGlyph3D>::New();
glyph->SetInputConnection(mask->GetOutputPort());
glyph->SetSourceConnection(m_arrow->GetOutputPort());
glyph->SetVectorModeToUseVector();
glyph->SetScaleFactor(0.1);
//glyph->SetVectorModeToVectorRotationOff();
//glyph->SetColorModeToColorByScale();
glyph->SetScaleModeToScaleByVector();

//glyph->SetColorMode(0);
using std::string;
string qq = glyph->GetScaleModeAsString();
qq = glyph->GetColorModeAsString();
glyph->Update();

vtkSmartPointer<vtkUnsignedCharArray> cellColors =
vtkSmartPointer<vtkUnsignedCharArray>::New();
cellColors->SetNumberOfComponents(3);
cellColors->InsertNextTupleValue(red);
cellColors->InsertNextTupleValue(green);
m_cone->GetOutput()->GetCellData()->SetScalars(scalars);

vtkSmartPointer<vtkIntArray> pointfield =
vtkSmartPointer<vtkIntArray>::New();
pointfield->SetName("Field");
pointfield->SetNumberOfComponents(3);
pointfield->InsertNextTuple3(1, 0, 0);
pointfield->InsertNextTuple3(2, 0, 0);
pointfield->InsertNextTuple3(3, 0, 0);
pointfield->InsertNextTuple3(4, 0, 0);
pointfield->InsertNextTuple3(5, 0, 0);
m_cone->GetOutput()->GetPointData()->AddArray(pointfield);


vtkSmartPointer<vtkLookupTable> m_table = vtkSmartPointer<vtkLookupTable>::New();
m_table->SetNumberOfColors(4);
m_table->SetTableValue(0, 1.0, 0, 0, 0);
m_table->SetTableValue(1, 0, 1.0, 0, 0);
m_table->SetTableValue(2, 0, 0, 1.0, 0);
m_table->SetTableValue(3, 0, 0, 0, 1.0);
//m_table->SetNumberOfColors(255);
m_table->Build();

vtkSmartPointer<vtkPolyDataMapper> originMapper =
vtkSmartPointer<vtkPolyDataMapper>::New();
originMapper->SetInputConnection(m_cone->GetOutputPort());
//originMapper->SetInputData(cube);
//originMapper->ScalarVisibilityOff();
originMapper->SetScalarRange(0,7);


vtkSmartPointer<vtkLookupTable> lut =
vtkSmartPointer<vtkLookupTable>::New();
lut->SetNumberOfTableValues(8);
lut->Build();
//lut->SetTableValue(0, 0, 0, 0, 1);
lut->SetTableValue(1, 0.8900, 0.8100, 0.3400, 1);
lut->SetTableValue(2, 1.0000, 0.3882, 0.2784, 1);
lut->SetTableValue(3, 0.9608, 0.8706, 0.7020, 1);
lut->SetTableValue(4, 0.9020, 0.9020, 0.9804, 1);
lut->SetTableValue(5, 1.0000, 0.4900, 0.2500, 1);
lut->SetTableValue(6, 0.5300, 0.1500, 0.3400, 1);
lut->SetTableValue(7, 0.9804, 0.5020, 0.4471, 1);
//lut->SetTableValue(8, 0.7400, 0.9900, 0.7900, 1);
//lut->SetTableValue(9, 0.2000, 0.6300, 0.7900, 1);

vtkLookupTable *pColorTable = vtkLookupTable::New();
//设置颜色表中的颜色
pColorTable->SetNumberOfColors(8);
///*pColorTable->SetTableValue(0,1.0,0.0,0.0,1.0);
pColorTable->SetTableValue(0, 1.0, 0.0, 0.0, 1.0);
pColorTable->SetTableValue(1, 0.0, 1.0, 0.0, 1.0);
pColorTable->SetTableValue(2, 1.0, 1.0, 0.0, 1.0);
pColorTable->SetTableValue(3, 0.0, 0.0, 1.0, 1.0);
pColorTable->SetTableValue(4, 1.0, 0.0, 1.0, 1.0);
pColorTable->SetTableValue(5, 0.0, 1.0, 1.0, 1.0);
pColorTable->SetTableValue(6, 1.0, 1.0, 1.0, 1.0);
pColorTable->SetTableValue(7, 0.0, 0.0, 0.0, 1.0);
pColorTable->Build();


originMapper->SetLookupTable(pColorTable);
vtkSmartPointer<vtkActor> originActor =
vtkSmartPointer<vtkActor>::New();
originActor->SetMapper(originMapper);
//originActor->GetProperty()->SetColor(1, 0, 0);


vtkSmartPointer<vtkPolyDataMapper> glyphMapper =
vtkSmartPointer<vtkPolyDataMapper>::New();
glyphMapper->SetInputData(glyph->GetOutput());
//	glyphMapper->ScalarVisibilityOff();
//	glyphMapper->SetScalarRange(0,550);
//	glyphMapper->SetLookupTable(lut);

vtkSmartPointer<vtkActor> glyphActor =
vtkSmartPointer<vtkActor>::New();
glyphActor->SetMapper(glyphMapper);
//glyphActor->GetProperty()->SetColor(1, 0, 0);

vtkSmartPointer<vtkPolyDataMapper> myarrowmap = vtkSmartPointer<vtkPolyDataMapper>::New();
myarrowmap->SetInputConnection(reader->GetOutputPort());

vtkSmartPointer<vtkActor> m_at2 = vtkSmartPointer<vtkActor>::New();
m_at2->SetMapper(myarrowmap);
m_at2->GetProperty()->SetColor(1, 0, 0);
vtkSmartPointer<vtkRenderer> glyphRenderer =
vtkSmartPointer<vtkRenderer>::New();
//	glyphRenderer->AddActor(originActor);
glyphRenderer->AddActor(glyphActor);
//
//glyphRenderer->ResetCamera();
//glyphRenderer->SetBackground(0.1,0.2,0.4);

vtkSmartPointer<vtkRenderWindow> renderWindow =
vtkSmartPointer<vtkRenderWindow>::New();

renderWindow->AddRenderer(glyphRenderer);
renderWindow->SetSize(1280, 960);
renderWindow->Render();
renderWindow->SetWindowName("PolyDataNormal");

vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
vtkSmartPointer<vtkRenderWindowInteractor>::New();
renderWindowInteractor->SetRenderWindow(renderWindow);
renderWindowInteractor->Initialize();
renderWindowInteractor->Start();

return EXIT_SUCCESS;

}
*/
/*
int main()
{


vtkSmartPointer<vtkCylinderSource> cylinder =

vtkSmartPointer<vtkCylinderSource>::New();

cylinder->SetHeight(2.0);

cylinder->SetRadius(1.0);

cylinder->SetResolution(10);


vtkSmartPointer<vtkArrowSource> m_arrow = vtkSmartPointer<vtkArrowSource>::New();
m_arrow->SetShaftRadius(0.03);
m_arrow->SetTipLength(0.35);


vtkSmartPointer<vtkGlyph3D> glyph =
vtkSmartPointer<vtkGlyph3D>::New();
glyph->SetInputConnection(cylinder->GetOutputPort());
glyph->SetSourceConnection(m_arrow->GetOutputPort());
glyph->SetVectorModeToUseNormal();
glyph->SetScaleFactor(0.1);
glyph->SetColorMode(1);
glyph->Update();

vtkSmartPointer<vtkPolyDataMapper> originMapper =
vtkSmartPointer<vtkPolyDataMapper>::New();
originMapper->SetInputData(cylinder->GetOutput());

vtkSmartPointer<vtkActor> originActor =
vtkSmartPointer<vtkActor>::New();
originActor->SetMapper(originMapper);
originActor->GetProperty()->SetColor(1, 0, 0);

vtkSmartPointer<vtkPolyDataMapper> glyphMapper =
vtkSmartPointer<vtkPolyDataMapper>::New();
glyphMapper->SetInputData(glyph->GetOutput());

vtkSmartPointer<vtkActor> glyphActor =
vtkSmartPointer<vtkActor>::New();
glyphActor->SetMapper(glyphMapper);
glyphActor->GetProperty()->SetColor(0, 1, 0);

vtkSmartPointer<vtkRenderer> glyphRenderer =
vtkSmartPointer<vtkRenderer>::New();

glyphRenderer->AddActor(glyphActor);
glyphRenderer->AddActor(originActor);
//glyphRenderer->ResetCamera();
glyphRenderer->SetBackground(0.1, 0.2, 0.4);

vtkSmartPointer<vtkRenderWindow> renderWindow =
vtkSmartPointer<vtkRenderWindow>::New();

renderWindow->AddRenderer(glyphRenderer);
renderWindow->SetSize(640, 320);
renderWindow->Render();
renderWindow->SetWindowName("PolyDataNormal");

vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
vtkSmartPointer<vtkRenderWindowInteractor>::New();
renderWindowInteractor->SetRenderWindow(renderWindow);
renderWindowInteractor->Initialize();
renderWindowInteractor->Start();


return EXIT_SUCCESS;

}
*/


/*

int main()
{
vtkSmartPointer<vtkCylinderSource> cylinder =

vtkSmartPointer<vtkCylinderSource>::New();

cylinder->SetHeight(2.0);

cylinder->SetRadius(1.0);

cylinder->SetResolution(10);


vtkSmartPointer<vtkPolyDataReader> reader =
vtkSmartPointer<vtkPolyDataReader>::New();
reader->SetFileName("E:\\11.vtk");
//reader->SetFileName("E:\\11.vtk");
reader->Update();


vtkSmartPointer<vtkExtractEdges> m_edge =
vtkSmartPointer<vtkExtractEdges>::New();

m_edge->SetInputConnection(reader->GetOutputPort());

vtkSmartPointer<vtkTubeFilter> tubes =
vtkSmartPointer<vtkTubeFilter>::New();

tubes->SetInputConnection(m_edge->GetOutputPort());
tubes->SetRadius(0.0625);
tubes->SetVaryRadiusToVaryRadiusOff();
tubes->SetNumberOfSides(32);


// 	vtkSmartPointer<vtkMaskPoints> mask =
// 		vtkSmartPointer<vtkMaskPoints>::New();
// 	mask->SetInputConnection(normFilter->GetOutputPort());
// 	mask->SetMaximumNumberOfPoints(300);
// 	mask->RandomModeOn();



vtkSmartPointer<vtkArrowSource> arrow =
vtkSmartPointer<vtkArrowSource>::New();
arrow->Update();

vtkSmartPointer<vtkSphereSource> sphere =
vtkSmartPointer<vtkSphereSource>::New();
sphere->SetThetaResolution(8);
sphere->SetPhiResolution(8);

vtkSmartPointer<vtkGlyph3D> glyph =
vtkSmartPointer<vtkGlyph3D>::New();
glyph->SetInputData(reader->GetOutput());
glyph->SetSourceData(arrow->GetOutput());
//	glyph->ScalingOn();
glyph->SetScaleModeToScaleByVector();
glyph->SetScaleFactor(0.1);
//glyph->OrientOn();
//	glyph->ClampingOff();
glyph->SetVectorModeToUseNormal();
// 	glyph->SetIndexModeToOff();
glyph->Update();

//定义颜色映射表
vtkLookupTable *pColorTable = vtkLookupTable::New();
pColorTable->SetNumberOfColors(6);
pColorTable->SetTableValue(0, 1.0, 0.0, 1.0, 1.0);
pColorTable->SetTableValue(1, 0.0, 1.0, 1.0, 1.0);
pColorTable->SetTableValue(2, 1.0, 1.0, 1.0, 1.0);
pColorTable->SetTableValue(3, 1.0, 0.0, 1.0, 1.0);
pColorTable->SetTableValue(4, 0.0, 0.0, 1.0, 1.0);
pColorTable->SetTableValue(5, 1.0, 1.0, 0.0, 1.0);
pColorTable->Build();

vtkSmartPointer<vtkPolyDataMapper> originMapper =
vtkSmartPointer<vtkPolyDataMapper>::New();
originMapper->SetInputData(reader->GetOutput());
originMapper->SetScalarRange(0, 26);

vtkSmartPointer<vtkActor> originActor =
vtkSmartPointer<vtkActor>::New();
originActor->SetMapper(originMapper);
originActor->GetProperty()->SetColor(1, 0, 0);

vtkSmartPointer<vtkPolyDataMapper> glyphMapper =
vtkSmartPointer<vtkPolyDataMapper>::New();
glyphMapper->SetInputData(glyph->GetOutput());
glyphMapper->SetLookupTable(pColorTable);
glyphMapper->SetScalarRange(0, 7);

vtkSmartPointer<vtkActor> glyphActor =
vtkSmartPointer<vtkActor>::New();
glyphActor->SetMapper(glyphMapper);
glyphActor->GetProperty()->SetColor(0.1, 0.2, 0.4);

vtkSmartPointer<vtkPolyDataMapper> cyMapper =
vtkSmartPointer<vtkPolyDataMapper>::New();
cyMapper->SetInputConnection(cylinder->GetOutputPort());

vtkSmartPointer<vtkActor> cyActor =
vtkSmartPointer<vtkActor>::New();
cyActor->SetMapper(cyMapper);
cyActor->GetProperty()->SetColor(1., 0., 0.);

vtkSmartPointer<vtkRenderer> glyphRenderer =
vtkSmartPointer<vtkRenderer>::New();

glyphRenderer->AddActor(glyphActor);
//	glyphRenderer->AddActor(originActor);
glyphRenderer->ResetCamera();
glyphRenderer->SetBackground(1.0, 1.0, 1.0);

vtkSmartPointer<vtkRenderWindow> renderWindow =
vtkSmartPointer<vtkRenderWindow>::New();

renderWindow->AddRenderer(glyphRenderer);
renderWindow->SetSize(640, 320);
renderWindow->Render();
renderWindow->SetWindowName("PolyDataNormal");

vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
vtkSmartPointer<vtkRenderWindowInteractor>::New();
renderWindowInteractor->SetRenderWindow(renderWindow);
renderWindowInteractor->Initialize();
renderWindowInteractor->Start();

return EXIT_SUCCESS;
}
*/

#include "vtkOBJReader.h"
#include "vtkAppendPolyData.h"
#include "vtkJPEGReader.h"
#include "vtkDataObjectWriter.h"
#include "vtkAxesActor.h"
#include "vtkOrientationMarkerWidget.h"
#include "vtkTextureMapToCylinder.h"
#include "vtkTextureMapToSphere.h"
#include "vtkTextureMapToPlane.h"



#include "vtkSTLReader.h"






/******************************************************************************/
//obj的读取和输出
/******************************************************************************/
/*
int main()
{
vtkSmartPointer<vtkOBJReader> reader1 = vtkSmartPointer<vtkOBJReader>::New();
reader1->SetFileName("E:\\outputstl\\xueguan.stl");

vtkSmartPointer<vtkOBJReader> reader2 = vtkSmartPointer<vtkOBJReader>::New();
reader2->SetFileName("E:\\obj\\blood3.obj");


vtkSmartPointer<vtkSTLReader> reader3 = vtkSmartPointer<vtkSTLReader>::New();
reader3->SetFileName("E:\\outputstl\\test1.stl");


vtkSmartPointer<vtkAppendPolyData> appendFilter =
vtkSmartPointer<vtkAppendPolyData>::New();
appendFilter->AddInputConnection(reader1->GetOutputPort());
appendFilter->AddInputConnection(reader2->GetOutputPort());
//appendFilter->Update();


vtkSmartPointer<vtkJPEGReader> m_jpeg = vtkSmartPointer<vtkJPEGReader>::New();
m_jpeg->SetFileName("E:\\outputstl\\143650.jpg");

//添加纹理坐标
vtkSmartPointer<vtkTexture> m_texture = vtkSmartPointer<vtkTexture>::New();
m_texture->SetInputConnection(m_jpeg->GetOutputPort());
m_texture->InterpolateOn();


vtkSmartPointer<vtkSmoothPolyDataFilter> m_smooth = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();//拉普拉斯平滑

m_smooth->SetInputConnection(reader3->GetOutputPort());
m_smooth->SetNumberOfIterations(1000);



vtkSmartPointer<vtkTextureMapToCylinder> m_mapto = vtkSmartPointer<vtkTextureMapToCylinder>::New();

m_mapto->SetInputConnection(m_smooth->GetOutputPort());
m_mapto->Update();

vtkSmartPointer<vtkTextureMapToPlane> m_mapto2 = vtkSmartPointer<vtkTextureMapToPlane>::New();

m_mapto2->SetInputConnection(reader3->GetOutputPort());
m_mapto2->Update();

vtkSmartPointer<vtkTextureMapToSphere> m_mapto3 = vtkSmartPointer<vtkTextureMapToSphere>::New();

m_mapto3->SetInputConnection(reader3->GetOutputPort());
m_mapto3->Update();

//渲染多边形几何数据
vtkSmartPointer<vtkPolyDataMapper> cylinderMapper =vtkSmartPointer<vtkPolyDataMapper>::New();

//渲染场景中的数据的可视化表达
vtkSmartPointer<vtkActor> cylinderActor =vtkSmartPointer<vtkActor>::New();
vtkSmartPointer<vtkPolyDataMapper> mymapper =vtkSmartPointer<vtkPolyDataMapper>::New();
vtkSmartPointer<vtkPolyDataMapper> mymapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
vtkSmartPointer<vtkPolyDataMapper> mymapper3 = vtkSmartPointer<vtkPolyDataMapper>::New();
mymapper->SetInputConnection(m_mapto->GetOutputPort());
mymapper2->SetInputConnection(m_mapto2->GetOutputPort());
mymapper3->SetInputConnection(m_mapto3->GetOutputPort());

vtkSmartPointer<vtkActor> myactor =vtkSmartPointer<vtkActor>::New();
vtkSmartPointer<vtkActor> myactor2 = vtkSmartPointer<vtkActor>::New();
vtkSmartPointer<vtkActor> myactor3 = vtkSmartPointer<vtkActor>::New();

myactor->SetMapper(mymapper);
myactor->SetTexture(m_texture);

myactor2->SetMapper(mymapper2);
myactor2->SetTexture(m_texture);

myactor3->SetMapper(mymapper3);
myactor3->SetTexture(m_texture);

vtkSmartPointer<vtkAxesActor> m_axes = vtkSmartPointer<vtkAxesActor>::New();


cylinderActor->GetProperty()->SetColor(1.0, 0, 0);
cylinderActor->SetMapper(cylinderMapper);
//cylinderActor->SetMapper(arrowSource);
//	cylinderActor->SetTexture(texture);

cylinderMapper->SetInputConnection(mymapper->GetOutputPort());

cylinderActor->SetMapper(cylinderMapper);

//负责管理场景的渲染过程
vtkSmartPointer<vtkRenderer> renderer =vtkSmartPointer<vtkRenderer>::New();
vtkRenderer *ren2 = vtkRenderer::New();
vtkRenderer *ren3 = vtkRenderer::New();

renderer->AddActor(myactor);
ren2->AddActor(myactor2);
ren3->AddActor(myactor3);
//renderer->AddActor(cylinderActor);

//renderer->SetBackground(0.0, 0.0, 0.0);
// renderer->SetViewport(0, 0, 0.5, 0.5);
// ren2->SetViewport(0.5, 0, 1, 0.5);
//ren3->SetViewport( 0.5, 0.5,1,1);
// renderer->SetViewport( 0.5, 0.5,1,1);

//将操作系统和vtk渲染引擎连接在一起
vtkSmartPointer<vtkRenderWindow> renWin =

vtkSmartPointer<vtkRenderWindow>::New();

//renWin->AddRenderer(renderer);
renWin->AddRenderer(renderer);
//renWin->AddRenderer(ren3);

renWin->SetSize(800, 600);
//提供独立的响应事件
vtkSmartPointer<vtkRenderWindowInteractor> iren =

vtkSmartPointer<vtkRenderWindowInteractor>::New();

iren->SetRenderWindow(renWin);

// 	vtkSmartPointer<vtkOrientationMarkerWidget> m_weight = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
// 	m_weight->SetOutlineColor(1, 1, 1);
// 	m_weight->SetViewport(0, 0, 0.3, 0.3);
// 	m_weight->SetOrientationMarker(m_axes);
// 	m_weight->SetInteractor(iren);
// 	m_weight->SetEnabled(1);
// 	m_weight->InteractiveOn();


//交互器样式的一种，通过控制相机对物体操作
vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =

vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

iren->SetInteractorStyle(style);

// 	vtkSmartPointer<vtkPolyDataWriter> vtkWriter = vtkSmartPointer<vtkPolyDataWriter>::New();
// 	vtkWriter->SetInputData(cylinder->GetOutput());
// 	vtkWriter->SetFileName("test.vtk");
// 	vtkWriter->Write();

renWin->Render();

iren->Initialize();

iren->Start();
//system("pause");

std::cout << "start write" << endl;
vtkSmartPointer<vtkOBJExporter> porter = vtkSmartPointer<vtkOBJExporter>::New();
porter->SetFilePrefix("E:\\outputstl\\test1");
porter->SetInput(renWin);
porter->Write();

std::cout << "endl1111" << endl;


return 0;
}


#include "windows.h"
#include <iostream>
#include <string>
#include "vtkPlaneSource.h"

//啥都不是
/*
int main()
{


int i;
//梯形的顶点坐标
static float x[8][3] = { { 0, 0, 0 }, { 4, 0, 0 }, { 4, 4, 0 }, { 0, 4, 0 },
{ 1, 1, 1 }, { 3, 1, 1 }, { 3, 3, 1 }, { 1, 3, 1 } };
//4个顶点构成一个单元，一共6个单元
static vtkIdType y[6][4] = { { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 0, 1, 5, 4 },
{ 1, 2, 6, 5 }, { 2, 3, 7, 6 }, { 3, 0, 4, 7 } };

vtkPoints *points = vtkPoints::New();
for (i = 0; i < 8; i++)
points->InsertPoint(i, x[i]);

vtkCellArray *polys = vtkCellArray::New();
for (i = 0; i < 6; i++)
polys->InsertNextCell(4, y[i]);
//存储标量值
vtkFloatArray *scalars = vtkFloatArray::New();
vtkFloatArray *scalars22 = vtkFloatArray::New();
scalars22->SetNumberOfComponents(3);
double turples3[3];
turples3[0] = 0;
turples3[1] = 0;
turples3[2] = 1;


// 	for (i = 0; i < 6; i++)
// 	{
// 	scalars->InsertTuple1(i, i);
// 	scalars22->InsertTuple(i, turples3);
// 	}

//存储标量值
vtkFloatArray *vectors = vtkFloatArray::New();
vtkFloatArray *vectors22 = vtkFloatArray::New();
for (i = 0; i < 50; i++)
{
vectors->InsertTuple1(i, 10);
scalars22->InsertTuple3(i, 0, 1, 0);
}
for (i = 50; i < 100; i++)
vectors->InsertTuple1(i, 11);
scalars22->InsertTuple3(i,1, 0, 0);
for (i = 100; i < 130; i++)
vectors->InsertTuple1(i, 12);
scalars22->InsertTuple3(i, 0, 1.0, 0);
for (i = 130; i < 150; i++)
vectors->InsertTuple1(i, 13);
scalars22->InsertTuple3(i, 0, 0, 1);
for (i = 150; i < 200; i++)
vectors->InsertTuple1(i, 15);
scalars22->InsertTuple3(i, 1.0, 1, 1);
for (i = 200; i < 230; i++)
vectors->InsertTuple1(i, 17);
scalars22->InsertTuple3(i, 1, 1, 0);
for (i = 230; i < 260; i++)
vectors->InsertTuple1(i,18);
scalars22->InsertTuple3(i, 1.0, 1.0, 0.4);
for (i = 260; i < 300; i++)
vectors->InsertTuple1(i, 20);
scalars22->InsertNextTuple3(0.0, 0.0, 1.0);


// 	for (i = 350; i < 400; i++)
// 		vectors->InsertTuple1(i, 23);
// 	scalars22->InsertNextTuple3(0.0, 0.0, 1.0);

//构建多边形数据
vtkPolyData *cube = vtkPolyData::New();
cube->SetPoints(points);
//设定单元的组成方式
cube->SetPolys(polys);
cube->GetPointData()->SetScalars(scalars);
cube->GetPointData()->SetVectors(scalars22);

int wewe = cube->GetNumberOfPoints();

//定义颜色映射表
vtkLookupTable *pColorTable = vtkLookupTable::New();
// 	pColorTable->SetNumberOfColors(6);
// 	pColorTable->SetTableValue(0, 1.0, 0.0, 1.0, 1.0);
//  	pColorTable->SetTableValue(1, 0.0, 1.0, 1.0, 1.0);
//  	pColorTable->SetTableValue(2, 0.5, 1.0, 0.2, 0.7);
// 	pColorTable->SetTableValue(4, 1.0, 0.0, 1.0, 1.0);
// 	pColorTable->SetTableValue(3, 0.0, 0.0, 1.0, 1.0);
// 	pColorTable->SetTableValue(5, 1.0, 1.0, 0.0, 1.0);
//	pColorTable->SetValueRange(0, 1);
//	pColorTable->SetSaturationRange(1, 1);
//	pColorTable->SetHueRange(0.4, 0.9);
pColorTable->SetHueRange(0.667, 0);
//pColorTable->SetAlphaRange(0.2, 0.8);

pColorTable->Build();
int cnum = pColorTable->GetNumberOfColors();

vtkArrowSource *arrow = vtkArrowSource::New();

arrow->Update();

vtkSmartPointer<vtkCylinderSource> cylinder =

vtkSmartPointer<vtkCylinderSource>::New();

cylinder->SetHeight(2.0);

cylinder->SetRadius(1.0);

cylinder->SetResolution(10);

vtkSmartPointer<vtkPolyDataReader> reader =
vtkSmartPointer<vtkPolyDataReader>::New();
//reader->SetFileName("E:\\11.vtk");
reader->SetFileName("E:\\fran_cut.vtk");
reader->Update();

// 	vtkSmartPointer< vtkDICOMImageReader > reader = vtkSmartPointer< vtkDICOMImageReader >::New();
// 	//reader->SetDirectoryName("E:\\Release\\LHYSE9");
// 	reader->SetDirectoryName("E:\\SE2");
// 	reader->SetDataScalarTypeToUnsignedShort();
// 	reader->SetDataSpacing(1, 1, 1);
// 	reader->SetDataByteOrderToLittleEndian();
//
// 	// 	vtkSmartPointer<vtkContourFilter> skinExtractor =
// 	// 		vtkSmartPointer<vtkContourFilter>::New();
// 	// 	skinExtractor->SetInputConnection(reader->GetOutputPort());
// 	//
// 	// 	my_writer->SetInputConnection(skinExtractor->GetOutputPort());
// 	// 	my_writer->SetFileName("E:\\121.vtk");
// 	// 	my_writer->Write();
//
// 	vtkImageShiftScale *shiftScale = vtkImageShiftScale::New();
// 	shiftScale->SetInputConnection(reader->GetOutputPort());
// 	shiftScale->SetOutputScalarTypeToUnsignedChar();
//
// 	//	vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
//
// 	vtkSmartPointer<vtkImageShrink3D> m_shrink = vtkSmartPointer<vtkImageShrink3D>::New();//二次抽样
//
// 	m_shrink->SetShrinkFactors(0, 0, 0);//调节绘制图像的精细程度
// 	m_shrink->AveragingOn();
// 	m_shrink->SetInputConnection(reader->GetOutputPort());
//
// 	vtkSmartPointer<vtkContourFilter> m_skinExtractor = vtkSmartPointer<vtkContourFilter>::New();//生成等值面/线
//
// 	m_skinExtractor->SetInputConnection(m_shrink->GetOutputPort());
// 	m_skinExtractor->SetValue(0, 400);//调整阈值，400以上是骨组织
// 	//	m_skinExtractor->SetValue(1, 800);//调整阈值，400以上是骨组织

//reader->GetOutput()->GetPointData()->SetScalars(vectors);

vtkSmartPointer<vtkMaskPoints> mask =
vtkSmartPointer<vtkMaskPoints>::New();

mask->SetInputConnection(reader->GetOutputPort());
mask->SetMaximumNumberOfPoints(300);
mask->RandomModeOn();
mask->Update(); 	                                          //要在设置属性之前！！！！！！！！！！！！！！！！！
mask->GetOutput()->GetPointData()->SetScalars(vectors);
mask->GetOutput()->GetPointData()->SetVectors(scalars22);


vtkSmartPointer<vtkPolyDataWriter> mmyy = vtkSmartPointer<vtkPolyDataWriter>::New();

// 	mmyy->SetFileName("E:\\vector.dat");
// 	mmyy->SetInputData(mask->GetOutput());
// 	mmyy->Write();
// 	cout << "end" << endl;
// 	system("pause");

int qq = mask->GetOutput()->GetNumberOfPoints();

vtkGlyph3D *glyh = vtkGlyph3D::New();
glyh->SetSourceData(arrow->GetOutput());
glyh->SetInputData(mask->GetOutput());
//glyh->ScalingOn();
glyh->SetScaleFactor(0.002);
//glyh->OrientOn();
glyh->ClampingOff();
glyh->SetVectorModeToUseVector();
//	glyh->SetScaleModeToScaleByVectorComponents();
//	glyh->SetScaleModeToScaleByScalar();
glyh->SetColorModeToColorByVector();
//	glyh->SetIndexModeToOff();
glyh->Update();

vtkPolyDataMapper *cubeMapper22 = vtkPolyDataMapper::New();
cubeMapper22->SetInputData(glyh->GetOutput());
cubeMapper22->SetScalarRange(0,2);

cubeMapper22->SetLookupTable(pColorTable);
vtkActor *cubeActor22 = vtkActor::New();
cubeActor22->SetMapper(cubeMapper22);
//	cubeActor22->GetProperty()->SetColor(1, 0, 0);

//数据映射
vtkPolyDataMapper *cubeMapper = vtkPolyDataMapper::New();
cubeMapper->SetInputData(glyh->GetOutput());
//cubeMapper->SetScalarRange(1500, 2200);
//cubeMapper->SetLookupTable(pColorTable);
cubeMapper->ScalarVisibilityOff();
vtkActor *cubeActor = vtkActor::New();
cubeActor->SetMapper(cubeMapper);

//cubeActor->GetProperty()->SetColor(1, 1, 1);
vtkCamera *camera = vtkCamera::New();
camera->SetPosition(1, 1, 1);
camera->SetFocalPoint(0, 0, 0);

vtkRenderer *renderer = vtkRenderer::New();
vtkRenderWindow *renWin = vtkRenderWindow::New();
renWin->AddRenderer(renderer);

vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
iren->SetRenderWindow(renWin);
//	renderer->AddActor(cubeActor);
renderer->AddActor(cubeActor22);
renderer->SetActiveCamera(camera);
renderer->ResetCamera();
renderer->SetBackground(0.1, 0.2, 0.4);
renWin->SetSize(400, 400);
renWin->Render();
iren->Start();
//
// 	char m_buf[8];
// 	itoa(qq, m_buf,8);
//
// 	MessageBox(NULL, "rua", m_buf, MB_OK);
// 	std::cout << "rua" << endl;
//删除
points->Delete();
polys->Delete();
scalars->Delete();
cube->Delete();
cubeMapper->Delete();
cubeActor->Delete();
camera->Delete();
renderer->Delete();
renWin->Delete();
iren->Delete();
pColorTable->Delete();
return 0;
}
*/


#include <vtkVolumeTextureMapper2D.h>
#include "vtkVolumeTextureMapper3D.h"

//#define vtkRenderingCore_AUTOINIT 2(vtkRenderingFreeTypeOpenGL,vtkRenderingOpenGL)
//#define vtkRenderingVolume_AUTOINIT 1(vtkRenderingVolumeOpenGL)

// vtkDomainsChemistry_AUTOINIT = 1(vtkDomainsChemistryOpenGL2)
// vtkIOExport_AUTOINIT = 1(vtkIOExportOpenGL2)
// vtkRenderingContext2D_AUTOINIT = 1(vtkRenderingContextOpenGL2)
// vtkRenderingCore_INCLUDE = "E:/my projects/laoddat/CMakeFiles/vtkRenderingCore_AUTOINIT_vtkInteractionStyle_vtkRenderingFreeType_vtkRenderingOpenGL2.h"
// vtkRenderingOpenGL2_AUTOINIT = 1(vtkRenderingGL2PSOpenGL2)
// vtkRenderingVolume_AUTOINIT = 1(vtkRenderingVolumeOpenGL2)




//VTK_MODULE_INIT(vtkRenderingVolumeOpenGL)

// VTK_MODULE_INIT(vtkRenderingOpenGL2)
// VTK_MODULE_INIT(vtkRenderingContextOpenGL2)


/*********************************保存dat文件*********************************************/
/*
int main()
{
// 	vtkSmartPointer<vtkPolyDataReader> reader =
// 		vtkSmartPointer<vtkPolyDataReader>::New();
// 	reader->SetFileName("E:\\11.vtk");
// 	//reader->SetFileName("E:\\fran_cut.vtk");
// 	reader->Update();
// 	vtkSmartPointer<vtkVolumeTextureMapper3D> volumeMapper =
// 		vtkSmartPointer<vtkVolumeTextureMapper3D>::New();
// 	volumeMapper->SetInputData(reader->GetOutput());;
// 	/************************************************************************
// 	vtkSmartPointer<vtkVolumeProperty> volumeProperty =
// 		vtkSmartPointer<vtkVolumeProperty>::New();
// 	volumeProperty->SetInterpolationTypeToLinear();
// 	volumeProperty->ShadeOn();  //打开或者关闭阴影测试
// 	volumeProperty->SetAmbient(0.4);
// 	volumeProperty->SetDiffuse(0.6);  //漫反射
// 	volumeProperty->SetSpecular(0.2); //镜面反射
// 	//设置不透明度
// 	vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity =
// 		vtkSmartPointer<vtkPiecewiseFunction>::New();
// 	compositeOpacity->AddPoint(70, 0.00);
// 	compositeOpacity->AddPoint(90, 0.40);
// 	compositeOpacity->AddPoint(180, 0.60);
// 	volumeProperty->SetScalarOpacity(compositeOpacity); //设置不透明度传输函数
//
// 	//设置颜色属性
// 	vtkSmartPointer<vtkColorTransferFunction> color =
// 		vtkSmartPointer<vtkColorTransferFunction>::New();
// 	color->AddRGBPoint(0.000, 0.00, 0.00, 0.00);
// 	color->AddRGBPoint(64.00, 1.00, 0.52, 0.30);
// 	color->AddRGBPoint(190.0, 1.00, 1.00, 1.00);
// 	color->AddRGBPoint(220.0, 0.20, 0.20, 0.20);
// 	volumeProperty->SetColor(color);
// 	/*******************************************************************************
// 	vtkSmartPointer<vtkVolume> volume =
// 		vtkSmartPointer<vtkVolume>::New();
// 	volume->SetMapper(volumeMapper);
// 	volume->SetProperty(volumeProperty);
//
// 	vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
// 	ren->SetBackground(0, 1, 0);
// 	ren->AddVolume(volume);
//
// 	vtkSmartPointer<vtkRenderWindow> rw = vtkSmartPointer<vtkRenderWindow>::New();
// 	rw->AddRenderer(ren);
// 	rw->SetSize(480, 480);
// 	rw->Render();
// 	rw->SetWindowName("VolumeRendering by Texture2D");
//
// 	vtkSmartPointer<vtkRenderWindowInteractor> rwi =
// 		vtkSmartPointer<vtkRenderWindowInteractor>::New();
// 	rwi->SetRenderWindow(rw);
//
// 	ren->ResetCamera();
// 	rw->Render();
// 	rwi->Start();
//
// 	return 0;


// 	std::ofstream fout("E:\\a123.dat", std::ios::binary);
// 	std::ofstream fout2("E:\\a123new.dat");
// 	float nNum = 12;
// 	int qx = 1000;
// 	int x = 1111;
// 	int y = 1000;
// 	int z = 1000;
// 	int u = -2100;
// 	int v = 3000;
// 	int w =2100;
// 	int nNum2 = 7001;
// 	std::string str("Hello, world");
//
// 	std::string mys = to_string(x) + " " + to_string(y) + " " + to_string(z) + " " + to_string(u) + " " + to_string(v) + " " + to_string(w);
//
// 	string mfheader = "TITLE = \"MRI Result \"\r\nVARIABLES = \"X (mm)\"\"Y (mm)\"\"Z (mm)\"\"U (m/s)\"\"V (m/s)\"\"W (m/s)\"\"Speed (m/s)\"\r\nZONE T = \"ZONE 1 \"I = 256 J = 256, K = 1, F = POINT DT = (DOUBLE DOUBLE DOUBLE DOUBLE DOUBLE DOUBLE DOUBLE)\r\n";
//
// 	//string mfheader = "TITLE = \"MRI Result \"\r\nVARIABLES = \"X (mm)\"\"Y (mm)\"\"Z (mm)\"\"U (m/s)\"\"V (m/s)\"\"W (m/s)\"\"Speed (m/s)\"\r\nZONE T = \"ZONE 1 \"I = 256, J = 256, K = 1, F = POINT DT = (DOUBLE DOUBLE DOUBLE DOUBLE DOUBLE DOUBLE DOUBLE)\r\n";
//
//
// //	而写文本文件则比较简单，如下：
//
// 	string myspace = " ";
// 	string myran = "\r\n";
//
// 	cout << "start" << endl;
// // 	for (int i = 0; i < 10;i++)
// // 	{
// // 		nNum2 += i;
// // 	//	fout.write(str.c_str(), sizeof(char)* (str.size()));
// // 		fout.write((char*)&nNum2, sizeof(int));
// // 	//	fout.write(myspace.c_str(), sizeof(char)* (myspace.size()));
// // 	//	fout.write(to_string(nNum).c_str(), sizeof(char)* (to_string(nNum).size()));
// //
// // // 		fout << (int)nNum << " " << (int)nNum2 << endl;
// // 		//fout2 << x<< y<< z<< u<< v<<w;
// // 		fout2 << mys;
// //
// // 		//fout2 << to_string(nNum) << to_string(nNum2) << std::endl;
// // 	}
//
//
// 	int mz = 0;
//
// 	//fout.write(mfheader.c_str(), sizeof(char)* (mfheader.size()));
// 	//fout.write(myran.c_str(), sizeof(char)* (myran.size()));
// 	//fout2 << mfheader;
// 	for (int x = 0; x < 9;x++)
// 	{
// 		for (int y = 0; y < 9;y++)
// 		{
// 			//int mmmm = x + 1000;
// 			fout.write((char*)&x, sizeof(int));
// 		//	fout.write(myspace.c_str(), sizeof(char)* (myspace.size()));
// 			fout.write((char*)&y, sizeof(int));
// 		//	fout.write(myspace.c_str(), sizeof(char)* (myspace.size()));
// 			fout.write((char*)&mz, sizeof(int));
// 		//	fout.write(myspace.c_str(), sizeof(char)* (myspace.size()));
// 			fout.write((char*)&u, sizeof(int));
// 		//	fout.write(myspace.c_str(), sizeof(char)* (myspace.size()));
// 			fout.write((char*)&v, sizeof(int));
// 		//	fout.write(myspace.c_str(), sizeof(char)* (myspace.size()));
// 			fout.write((char*)&w, sizeof(int));
// 		//	fout.write(myspace.c_str(), sizeof(char)* (myspace.size()));
// 			fout.write((char*)&w, sizeof(int));
// 		//	fout.write(myran.c_str(), sizeof(char)* (myran.size()));
// 			//string qq = to_string(x) + " " + to_string(y) + " " + to_string(mz) + " " + to_string(u) + " " + to_string(v) + " " + to_string(w) + " " + to_string(w);
//
// 			//fout.write(qq.c_str(), sizeof(char)* (qq.size()));
//
// 		//	fout2 << x+1000 << " " << y+1000 << " " << mz+1000 << " " << u << " " << v << " " << w << " " << w;
// 			//fout2 << qq;
// 		//	fout2 << "\n";
//
// 		}
// 	}

// 	cout << "end" << endl;
// fout.close();
// 	fout2.close();
//
// 	std::ifstream readfile("E:\\ddddddd00000.dat", std::ios::binary);
//
// 	//char ch[256] = {0};
// 	int  ch[3] = {0};
//
// 	string asd;
// 	int numm = 0;
// 	while (!readfile.eof())
// 	{
// 		readfile.read((char*)(&ch[0]), sizeof(ch[0]));
// 		readfile.read((char*)(&ch[1]), sizeof(ch[1]));
// 		readfile.read((char*)(&ch[2]), sizeof(ch[2]));
//
// 		if (readfile.eof())
// 		{
// 			break;
// 		}
// 		if (ch[0] == 179)
// 		{
// 			if (ch[1] == -37)
// 			{
// 		//		cout << "rua" << endl;
// 			}
// 		}
// 		numm++;
// 	//	cout << ch << endl;
// 	}
//
// //	cout << numm << endl;
//
// 	system("pause");
//
// 	readfile.close();

typedef unsigned int PixelType;
//typedef int_fast16_t PixelType;
const unsigned int Dimension = 3;
typedef itk::Image<PixelType, Dimension> ImageType;
typedef itk::ImageFileReader<ImageType> ReaderType;
typedef itk::GDCMImageIO ImageIOType;
typedef itk::ImageToVTKImageFilter<ImageType> trans;
ReaderType::Pointer reader12[3];

ImageIOType::Pointer dicomIO1[3];
ImageType::Pointer image[3];

ImageType::SizeType size;
ImageType::IndexType index = { { 1, 1, 1 } };
ImageType::PixelType value[3];

INT16* pixel[3];

int nonnum = 0;
cout << "start" << endl;
for (int j = 11; j < 26; j++)//26
{
vtkSmartPointer< vtkDICOMImageReader > reader[3];
reader[0] = vtkDICOMImageReader::New();
reader[1] = vtkDICOMImageReader::New();
reader[2] = vtkDICOMImageReader::New();
//string mfn = "E:\\streamyes.dat";
string mfn = "E:\\dataofdcm\\allstream\\data" + to_string(j) + ".dat";
string mfn2 = "E:\\streamno.dat";
string mfheader = "TITLE = \"MRI Result \"\r\nVARIABLES = \"X (mm)\"\"Y (mm)\"\"Z (mm)\"\"U (m/s)\"\"V (m/s)\"\"W (m/s)\"\"Speed (m/s)\"\r\nZONE T = \"ZONE 1 \"I = 256, J = 256, K = 84, F = POINT DT = (DOUBLE DOUBLE DOUBLE DOUBLE DOUBLE DOUBLE DOUBLE)\r\n";
//i= j= 256

//文本
//		ofstream fout1(mfn2);
//		fout1 << mfheader;

//二进制
std::ofstream fout(mfn, std::ios::binary);
//	fout.write(mfheader.c_str(), sizeof(char)* (mfheader.size()));

for (int m = 0; m < 84; m++)//84
{

for (int i = 0; i < 3; i++)//3
{
//	reader12[i] = ReaderType::New();
//	dicomIO1[i] = ImageIOType::New();

//sprintf(t_fileName, "E:\\wang ya ming-4D Flow\\Anatomy\\A\\Z%02d.dcm", i+5);
string t_1fileName;
// 				if (i == 0)
// 				{
// 					t_1fileName = "E:\\dataofdcm\\phase 1\\Phase1_sag" + to_string(24) + "_ins4.dcm";
// 				}
if (i == 0)//0
{
t_1fileName = "E:\\dataofdcm\\mydata\\d1\\Z" + to_string(j + 25 * m) + ".dcm";
//t_1fileName = "E:\\dataofdcm\\phase 1\\Phase1_sag" + to_string(22 + m) + "_ins" + to_string(j) + ".dcm";
}
if (i == 1)
{
t_1fileName = "E:\\dataofdcm\\mydata\\d2\\Z" + to_string(j + 25 * m) + ".dcm";
//t_1fileName = "E:\\dataofdcm\\phase 2\\Phase2_sag" + to_string(22 + m) + "_ins" + to_string(j) + ".dcm";
}
if (i == 2)
{
t_1fileName = "E:\\dataofdcm\\mydata\\d3\\Z" + to_string(j + 25 * m) + ".dcm";
//t_1fileName = "E:\\dataofdcm\\phase 3\\Phase3_sag" + to_string(22 + m) + "_ins" + to_string(j) + ".dcm"; //"_ins4.dcm";
}

//vtk
reader[i]->SetFileName(t_1fileName.c_str());
reader[i]->SetDataScalarTypeToUnsignedShort();
reader[i]->SetDataSpacing(1, 1, 1);
reader[i]->SetDataByteOrderToLittleEndian();
reader[i]->Update();

//itk
// 				reader12[i] = ReaderType::New();
// 				dicomIO1[i] = ImageIOType::New();
// 				reader12[i]->SetFileName(t_1fileName);
// 				reader12[i]->SetImageIO(dicomIO1[i]);
// 				try
// 				{
// 					reader12[i]->Update();
// 				}
// 				catch (itk::ExceptionObject &err)
// 				{
// 					std::cerr << "Read Error" << std::endl;
// 					std::cerr << err << std::endl;
// 					return EXIT_FAILURE;
// 				}
//
// 				image[i] = reader12[i]->GetOutput();
//
// 				size = image[i]->GetLargestPossibleRegion().GetSize();
int dims[3] = { 0 };
reader[i]->GetOutput()->GetDimensions(dims);

}

string myran = "\r\n";
string myspace = " ";

for (int y = 0; y < 256; y++)//size[0]
{
float mysum = 0;
for (int x = 0; x < 256; x++)//size[1]
{
mysum = 0;
index[0] = x;//x
index[1] = y;//y
index[2] = 0;
string my_value;
my_value = to_string(x) + " " + to_string(y) + " " + to_string(m);

//文本
//						fout1 << my_value;
// 						fout1 << x << endl;
// 						fout1 << " " << endl;
// 						fout1 << y << endl;
// 						fout1 << " " << endl;
// 						fout1 << m << endl;

//二进制
//	fout.write((char*)&x, sizeof(int));
//	fout.write(myspace.c_str(), sizeof(char)* (myspace.size()));
//	fout.write((char*)&y, sizeof(int));
//	fout.write(myspace.c_str(), sizeof(char)* (myspace.size()));
//	fout.write((char*)&m, sizeof(int));
//	fout.write(my_value.c_str(), sizeof(char)* (my_value.size()));

value[1] = value[0] = value[2] = 0;

for (int n = 0; n < 3; n++)//3
{
//image->SetPixel(index, 0);
int qwe = 0;
int asd = 0;
//	value[n] = image[n]->GetPixel(index);//itk
//vtk
pixel[n] = (INT16*)reader[n]->GetOutput()->GetScalarPointer(x, y, 0);
//	cout <<(int)value[n]<<" "<<int(*pixel[n]) << endl;

//文本
//							fout1 << myspace;


//二进制
//	fout.write(myspace.c_str(), sizeof(char)* (myspace.size()));

//	int outvalue = (int)value[n];//((int)value[n]) / 0.018//itk
int outvalue = int(*pixel[n]);


//文本
//							fout1 << outvalue;/// 0.018;
//二进制
fout.write((char*)&outvalue, sizeof(int));//!!!!!!!!!!!!!!!!!!!

//		cout << int(*ew) << endl;
//	fout.write(to_string(outvalue).c_str(), sizeof(char)* (to_string(outvalue).size()));

//	fout.write(to_string(int(*value22[n])).c_str(), sizeof(char)* (to_string(int(*value22[n])).size()));

mysum += (outvalue)*(outvalue);
//		mysum += ((int(*value22[n])))*((int(*value22[n])));

}

//文本
//		 						fout1 << myspace;
//								fout1 << sqrt(mysum);
//		 						fout1 << myran;
//二进制
//	fout.write(myspace.c_str(), sizeof(char)* (myspace.size()));
//	fout.write((char*)&fvalue, sizeof(float));
//	float fvalue = sqrt(mysum);
//	fout.write(to_string(fvalue).c_str(), sizeof(char)* (to_string(fvalue).size()));
//	fout.write(myran.c_str(), sizeof(char)* (myran.size()));

}


}
//cout <<"num:: " <<nonnum << endl;
}
fout.close();

// 		delete[] pixel;
// 		delete[] value;


//	fout1.close();
}


cout << "end" << endl;


//	MessageBox(NULL, "rua", "rua", MB_OK);
return 0;
}

*/


#include "vtkSTLReader.h"
/*
int main()
{

// 	vtkSmartPointer<vtkPolyDataReader> reader1 = vtkSmartPointer<vtkPolyDataReader>::New();
//
// 	reader1->SetFileName("E:\\11.vtk");
// 	reader1->Update();

// 	vtkSmartPointer<vtkOBJReader> reader1 = vtkSmartPointer<vtkOBJReader>::New();
// 	reader1->SetFileName("E:\\obj\\blood1.obj");

vtkSmartPointer<vtkSTLReader> reader1 = vtkSmartPointer<vtkSTLReader>::New();
reader1->SetFileName("E:\\my.stl");
//	reader1->SetFileName("E:\\obj\\blood1.stl");

vtkSmartPointer<vtkSmoothPolyDataFilter> m_smooth = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();//拉普拉斯平滑

m_smooth->SetInputConnection(reader1->GetOutputPort());
m_smooth->SetNumberOfIterations(200);


vtkSmartPointer<vtkJPEGReader> m_jpeg = vtkSmartPointer<vtkJPEGReader>::New();
m_jpeg->SetFileName("E:\\outputstl\\a5.jpg");

vtkSmartPointer<vtkTexture> m_texture = vtkSmartPointer<vtkTexture>::New();

//int a;

m_texture->SetInputConnection(m_jpeg->GetOutputPort());

vtkSmartPointer<vtkTextureMapToCylinder> m_mapto = vtkSmartPointer<vtkTextureMapToCylinder>::New();

m_mapto->SetInputConnection(m_smooth->GetOutputPort());
m_mapto->Update();

//渲染多边形几何数据
vtkSmartPointer<vtkPolyDataMapper> cylinderMapper =

vtkSmartPointer<vtkPolyDataMapper>::New();

//渲染场景中的数据的可视化表达
vtkSmartPointer<vtkActor> cylinderActor =

vtkSmartPointer<vtkActor>::New();
vtkSmartPointer<vtkPolyDataMapper> mymapper =

vtkSmartPointer<vtkPolyDataMapper>::New();
mymapper->SetInputConnection(m_mapto->GetOutputPort());

vtkSmartPointer<vtkActor> myactor =

vtkSmartPointer<vtkActor>::New();

myactor->SetMapper(mymapper);
myactor->SetTexture(m_texture);

vtkSmartPointer<vtkAxesActor> m_axes = vtkSmartPointer<vtkAxesActor>::New();


//	cylinderActor->GetProperty()->SetColor(1.0, 0, 0);
cylinderActor->SetMapper(cylinderMapper);
//cylinderActor->SetMapper(arrowSource);
//	cylinderActor->SetTexture(texture);

cylinderMapper->SetInputConnection(mymapper->GetOutputPort());

cylinderActor->SetMapper(cylinderMapper);

//负责管理场景的渲染过程
vtkSmartPointer<vtkRenderer> renderer =

vtkSmartPointer<vtkRenderer>::New();
renderer->AddActor(myactor);
//renderer->AddActor(cylinderActor);

renderer->SetBackground(0.0, 0.0, 0.0);
//renderer->SetViewport(0, 0, 0.5, 0.5);
//renderer->SetViewport(0.5, 0, 1, 0.5);
//renderer->SetViewport( 0.5, 0.5,0.5,1);
//renderer->SetViewport( 0.5, 0.5,1,1);

//将操作系统和vtk渲染引擎连接在一起
vtkSmartPointer<vtkRenderWindow> renWin =

vtkSmartPointer<vtkRenderWindow>::New();

renWin->AddRenderer(renderer);

renWin->SetSize(300, 300);
//提供独立的响应事件
vtkSmartPointer<vtkRenderWindowInteractor> iren =

vtkSmartPointer<vtkRenderWindowInteractor>::New();

iren->SetRenderWindow(renWin);

// 	vtkSmartPointer<vtkOrientationMarkerWidget> m_weight = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
// 	m_weight->SetOutlineColor(1, 1, 1);
// 	m_weight->SetViewport(0, 0, 0.3, 0.3);
// 	m_weight->SetOrientationMarker(m_axes);
// 	m_weight->SetInteractor(iren);
// 	m_weight->SetEnabled(1);
// 	m_weight->InteractiveOn();


//交互器样式的一种，通过控制相机对物体操作
vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =

vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

iren->SetInteractorStyle(style);


// 	vtkSmartPointer<vtkPolyDataWriter> vtkWriter = vtkSmartPointer<vtkPolyDataWriter>::New();
// 	vtkWriter->SetInputData(cylinder->GetOutput());
// 	vtkWriter->SetFileName("test.vtk");
// 	vtkWriter->Write();

renWin->Render();

iren->Initialize();

iren->Start();
vtkSmartPointer<vtkOBJExporter> porter = vtkSmartPointer<vtkOBJExporter>::New();
// 	porter->SetFilePrefix("E:\\outputstl\\blood");
// 	porter->SetInput(renWin);
// 	porter->Write();

std::cout << "endl1111" << endl;

system("pause");
return 0;
}
*/
/******************************************mri三维重构*****************************************************/
#include "vtkImageCast.h"

#include "vtkMarchingCubes.h"
/*
int main()
{

	double m_pre = (double)40/100;


vtkSmartPointer<vtkPolyDataWriter> my_writer = vtkSmartPointer<vtkPolyDataWriter>::New();
vtkSmartPointer< vtkDICOMImageReader > reader = vtkSmartPointer< vtkDICOMImageReader >::New();
reader->SetDirectoryName("E:\\dataofdcm\\Snake\\onetime");
//reader->SetDirectoryName("E:\\dataofdcm\\mydata\\onetime");
reader->SetDataScalarTypeToUnsignedShort();
reader->SetDataSpacing(1, 1, 1);
reader->SetDataByteOrderToLittleEndian();
reader->Update();

vtkVolume16Reader *v16 = vtkVolume16Reader::New();
v16->SetFilePrefix("E:\\dataofdcm\\Snake\\onetime\\Z");
v16->SetFilePattern("%s%d.dcm");
//	v16->SetFilePrefix("E:\\dataofdcm\\phase 2\\Phase2_sag");
//	v16->SetFilePattern("%s%d_ins4.dcm");
v16->SetDataDimensions(256, 256);
v16->SetImageRange(1, 25);//84
v16->SetDataByteOrderToLittleEndian();
v16->SetDataSpacing(1, 1, 1);
v16->Update();

vtkSmartPointer<vtkImageShrink3D> m_shrink = vtkSmartPointer<vtkImageShrink3D>::New();//二次抽样

m_shrink->SetShrinkFactors(0, 0, 0);//调节绘制图像的精细程度
m_shrink->AveragingOn();
m_shrink->SetInputConnection(reader->GetOutputPort());
m_shrink->Update();

vtkSmartPointer<vtkContourFilter> m_skinExtractor = vtkSmartPointer<vtkContourFilter>::New();//生成等值面/线

m_skinExtractor->SetInputConnection(m_shrink->GetOutputPort());
m_skinExtractor->SetValue(500, 1500);//调整阈值，400以上是骨组织


vtkSmartPointer<vtkMarchingCubes> m_marchingcubes = vtkSmartPointer<vtkMarchingCubes>::New();//移动立方体

m_marchingcubes->SetInputConnection(reader->GetOutputPort());
m_marchingcubes->SetValue(0, 400);


vtkSmartPointer<vtkStripper> m_stripper = vtkSmartPointer<vtkStripper>::New();//创造三角形条

m_stripper->SetInputConnection(m_skinExtractor->GetOutputPort());

vtkTriangleFilter* triangle = vtkTriangleFilter::New();
triangle->SetInputConnection(m_skinExtractor->GetOutputPort());


vtkSmartPointer<vtkDecimatePro> m_deci = vtkSmartPointer<vtkDecimatePro>::New();//减少网格中三角形的数量

m_deci->SetTargetReduction(0.3);//减少到70%
m_deci->SetInputConnection(triangle->GetOutputPort());
//m_deci->Update();

vtkSmartPointer<vtkSmoothPolyDataFilter> m_smooth = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();//拉普拉斯平滑

m_smooth->SetInputConnection(m_skinExtractor->GetOutputPort());
m_smooth->SetNumberOfIterations(200);

vtkSmartPointer<vtkPolyDataNormals> m_skinNormals = vtkSmartPointer<vtkPolyDataNormals>::New();//计算多边形网格的法线

m_skinNormals->SetInputConnection(m_smooth->GetOutputPort());
m_skinNormals->SetComputeCellNormals(1);
m_skinNormals->SetComputePointNormals(1);
m_skinNormals->SetFeatureAngle(60.0);//设置定义的锐角
//	m_skinNormals->Update();



//数据映射
vtkPolyDataMapper *cubeMapper = vtkPolyDataMapper::New();
cubeMapper->SetInputConnection(m_skinNormals->GetOutputPort());
//cubeMapper->SetScalarRange(1500, 2200);
//cubeMapper->SetLookupTable(pColorTable);
cubeMapper->ScalarVisibilityOff();

vtkActor *cubeActor = vtkActor::New();
cubeActor->SetMapper(cubeMapper);
cubeActor->GetProperty()->SetColor(1, 1, 1);

vtkCamera *camera = vtkCamera::New();
camera->SetPosition(1, 1, 1);
camera->SetFocalPoint(0, 0, 0);

vtkRenderer *renderer = vtkRenderer::New();
vtkRenderWindow *renWin = vtkRenderWindow::New();
renWin->AddRenderer(renderer);

vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
iren->SetRenderWindow(renWin);
renderer->AddActor(cubeActor);
renderer->SetActiveCamera(camera);
renderer->ResetCamera();
renderer->SetBackground(0.1, 0.2, 0.4);
renWin->SetSize(400, 400);
renWin->Render();
iren->Start();

return 0;

}
*/

#include "vtkPoints.h"
#include "vtkCellArray.h"

/*
int main()
{
vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();

vtkSmartPointer<vtkPolygon> polygon = vtkSmartPointer<vtkPolygon>::New();

vtkSmartPointer<vtkPoints> m_points = vtkSmartPointer<vtkPoints>::New();
for (int i = 0; i< 4;i++)
{
for (int j = 0; j < 4;j++)
{
vtkIdType m_pid[1];

m_pid[0] = m_points->InsertNextPoint(i, j, 0);
vertices->InsertNextCell(3, m_pid);
}
}

vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
polydata->SetPoints(m_points);
polydata->SetVerts(vertices);

vtkSmartPointer<vtkPolyDataWriter> my_writer =
vtkSmartPointer<vtkPolyDataWriter>::New();
my_writer->SetFileName("E:\\101.vtk");

vtkSmartPointer< vtkDICOMImageReader > reader = vtkSmartPointer< vtkDICOMImageReader >::New();
//reader->SetDirectoryName("E:\\Release\\LHYSE9");
reader->SetDirectoryName("E:\\dataofdcm\\mydata\\oooeee");
reader->SetDataScalarTypeToUnsignedChar();
reader->SetDataSpacing(1, 1, 1);
reader->SetDataByteOrderToLittleEndian();
reader->Update();

int rwwr = reader->GetOutput()->GetNumberOfPoints();

int dims[3];
reader->GetOutput()->GetDimensions(dims);

int qqqnum = 0;
double mmdd[3];

reader->GetOutput()->GetPoint(2, mmdd);

for (int k = 0; k < dims[2]; k++)

{	for (int i = 0; i < dims[0]; i++)
{
for (int j = 0; j < dims[1]; j++)
{

int* pixel = (int*)reader->GetOutput()->GetScalarPointer(i, j, k);

if (int(*pixel) == 100)
{
int gg = 80;
}

if (int(*pixel) == 232)
{
int gg = 40;
}

if (int(*pixel)!=0)
{
//	cout << i << " " << j << " " << k << " " << int(*pixel)<<" "<< int(pixel) << endl;
}

cout << i << " " << j << " " <<k<< " " << int(*pixel) << endl;
string q2 = to_string(i) + " " + to_string(j) + " " + to_string(k) + " " + to_string(int(*pixel));
//	string mmyyy = to_string(int(*pixel));
//	fout << q2;
//fout << "\n";
if (int(*pixel)!=0)
{
qqqnum++;
}

}

}
}

system("pause");

//定义颜色映射表
vtkLookupTable *pColorTable = vtkLookupTable::New();
// 	pColorTable->SetNumberOfColors(6);
// 	pColorTable->SetTableValue(0, 1.0, 0.0, 1.0, 1.0);
//  	pColorTable->SetTableValue(1, 0.0, 1.0, 1.0, 1.0);
//  	pColorTable->SetTableValue(2, 0.5, 1.0, 0.2, 0.7);
// 	pColorTable->SetTableValue(4, 1.0, 0.0, 1.0, 1.0);
// 	pColorTable->SetTableValue(3, 0.0, 0.0, 1.0, 1.0);
// 	pColorTable->SetTableValue(5, 1.0, 1.0, 0.0, 1.0);
//	pColorTable->SetValueRange(0, 1);
//	pColorTable->SetSaturationRange(1, 1);
//	pColorTable->SetHueRange(0.4, 0.9);
pColorTable->SetHueRange(0.667, 0);
//pColorTable->SetAlphaRange(0.2, 0.8);

vtkArrowSource *arrow = vtkArrowSource::New();

vtkSmartPointer<vtkMaskPoints> mask =
vtkSmartPointer<vtkMaskPoints>::New();

mask->SetInputData(reader->GetOutput());
mask->SetMaximumNumberOfPoints(100);
mask->RandomModeOn();
mask->Update();

//mask->GetOutput()->GetPointData()->SetScalars(vectors);
//mask->GetOutput()->GetPointData()->SetVectors(scalars22);
int qq = mask->GetOutput()->GetNumberOfPoints();

vtkGlyph3D *glyh = vtkGlyph3D::New();
glyh->SetSourceData(arrow->GetOutput());
glyh->SetInputData(mask->GetOutput());
//	glyh->SetInputData(cube);
//glyh->ScalingOn();
glyh->SetScaleFactor(2);
glyh->OrientOn();
// 	glyh->ClampingOff();
//	glyh->SetVectorModeToUseNormal();
glyh->SetVectorModeToUseVector();
glyh->SetScaleModeToScaleByScalar();
glyh->SetColorModeToColorByVector();

//	glyh->SetIndexModeToOff();
glyh->Update();

vtkPolyDataMapper *cubeMapper22 = vtkPolyDataMapper::New();
cubeMapper22->SetInputData(glyh->GetOutput());
cubeMapper22->SetScalarRange(0, 17);

cubeMapper22->SetLookupTable(pColorTable);
vtkActor *cubeActor22 = vtkActor::New();
cubeActor22->SetMapper(cubeMapper22);
//	cubeActor22->GetProperty()->SetColor(1, 0, 0);

//数据映射
vtkPolyDataMapper *cubeMapper = vtkPolyDataMapper::New();
//cubeMapper->SetInputData(reader->GetOutput());
//cubeMapper->SetScalarRange(1500, 2200);
//cubeMapper->SetLookupTable(pColorTable);
cubeMapper->ScalarVisibilityOff();
vtkActor *cubeActor = vtkActor::New();
cubeActor->SetMapper(cubeMapper);

cubeActor->GetProperty()->SetColor(1, 1, 1);
vtkCamera *camera = vtkCamera::New();
camera->SetPosition(1, 1, 1);
camera->SetFocalPoint(0, 0, 0);

vtkRenderer *renderer = vtkRenderer::New();
vtkRenderWindow *renWin = vtkRenderWindow::New();
renWin->AddRenderer(renderer);

vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
iren->SetRenderWindow(renWin);
renderer->AddActor(cubeActor);
renderer->AddActor(cubeActor22);
renderer->SetActiveCamera(camera);
renderer->ResetCamera();
renderer->SetBackground(0.1, 0.2, 0.4);
renWin->SetSize(400, 400);
renWin->Render();
iren->Start();

}
*/






/**************************************画向量场**********************************************/

/*
int main()
{

vtkSmartPointer<vtkPolyDataWriter> my_writer = vtkSmartPointer<vtkPolyDataWriter>::New();
vtkSmartPointer< vtkDICOMImageReader > reader = vtkSmartPointer< vtkDICOMImageReader >::New();
//reader->SetDirectoryName("E:\\Release\\LHYSE9");
//	reader->SetDirectoryName("E:\\SE2");//E:\dataofdcm\mydata\d0
reader->SetDirectoryName("E:\\dataofdcm\\mydata\\onetime");

reader->SetDataScalarTypeToUnsignedShort();
reader->SetDataSpacing(1, 1, 1);
reader->SetDataByteOrderToLittleEndian();
reader->Update();
// 		int tt66 = reader->GetOutput()->GetNumberOfPoints();

// 	my_writer->SetInputConnection(skinExtractor->GetOutputPort());
// 	my_writer->SetFileName("E:\\121.vtk");
// 	my_writer->Write();

vtkImageShiftScale *shiftScale = vtkImageShiftScale::New();
shiftScale->SetInputConnection(reader->GetOutputPort());
shiftScale->SetOutputScalarTypeToUnsignedChar();

vtkVolume16Reader *v16 = vtkVolume16Reader::New();
v16->SetFilePrefix("E:\\dataofdcm\\mydata\\d0\\Z");
v16->SetFilePattern("%s%d.dcm");
//	v16->SetFilePrefix("E:\\dataofdcm\\phase 2\\Phase2_sag");
//	v16->SetFilePattern("%s%d_ins4.dcm");
v16->SetDataDimensions(256, 256);
v16->SetImageRange(1, 84);//84
v16->SetDataByteOrderToLittleEndian();
v16->SetDataSpacing(1, 1, 2);
v16->Update();

double *mypixel;
mypixel  =  v16->GetOutput()->GetPoint(1000);

int yy = (int)(*mypixel);

int myvec = 10;

vtkFloatArray* myfl = vtkFloatArray::New();
myfl->SetNumberOfComponents(3);
int ssss = v16->GetOutput()->GetNumberOfPoints();

std::ifstream readfile("E:\\dataofdcm\\allstream\\data1.dat", std::ios::binary);//dataofdcm\\

int  ch[3] = { 0 };
int ttt = 0;
int asd = 1;

int mina = 0;
int maxa = 0;

//	cout << mina << " " << maxa << endl;
int nonnum = 0;
int row = 0;
int line = 0;
while (!readfile.eof())
{

if (asd%256 == 0)
{
line++;
}
if (row%256 == 0)
{
row = 0;
}
if (line%256==0)
{
line = 0;
}

readfile.read((char*)(&ch[0]), sizeof(ch[0]));
if (readfile.eof())
{
break;
}
readfile.read((char*)(&ch[1]), sizeof(ch[1]));
if (readfile.eof())
{
break;
}
readfile.read((char*)(&ch[2]), sizeof(ch[2]));

if (readfile.eof())
{
break;
}

myfl->InsertTuple3(asd, ch[0], ch[1],ch[2]);
//
// 			ttt = ch[0] * ch[0] + ch[1] * ch[1] + ch[2] * ch[2];
//
// 			ttt = sqrt(ttt);

//cout << ch[0] << " " << ch[1] << " " << ch[2] <<endl;
asd++;
row++;
if (ch[0] == 0 && ch[1] == 0 && ch[2] == 0)
{
}
else
{
//			cout << row << " " << line << " ::" << ch[0] << " " << ch[1] << " " << ch[2] << " " << endl;
}
}
for (int i = 19110; i < 31234;i++)
{
//myfl->InsertTuple3(i*256+50, 100, 1000, 1600);
//myfl->InsertTuple3(i * 256 + 60, 100, 1000, 1600);
//	myfl->InsertTuple3(i * 256 + 70, 100, 1000, 1600);
//	myfl->InsertTuple3(i, 100, 1000, 1600);
//myfl->InsertTuple3(i * 256 + 100, 100, 1000, 1600);
//myfl->InsertTuple3(i * 256 + 90, 100, 1000, 1600);
//	myfl->InsertTuple3(i, 100, 1000, 1600);
}
//	myfl->InsertTuple3(asd, ch[0], ch[1], ch[2]);
//		cout << mina << "     " << maxa << endl;
cout << asd << endl;
//		cout << nonnum << endl;
//	system("pause");
reader->GetOutput()->GetPointData()->SetVectors(myfl);
v16->GetOutput()->GetPointData()->SetVectors(myfl);
v16->Update();
// 		vtkSmartPointer<vtkStructuredGridWriter> struww = vtkSmartPointer<vtkStructuredGridWriter>::New();
// 		struww->SetInputConnection(v16->GetOutputPort());
// 		struww->SetFileName("E:\\ry3.vtk");
// 		struww->Write();
// 	 	struww->Update();
// 		system("pause");

vtkSmartPointer<vtkImageShrink3D> m_shrink = vtkSmartPointer<vtkImageShrink3D>::New();//二次抽样

m_shrink->SetShrinkFactors(0, 0, 0);//调节绘制图像的精细程度
m_shrink->AveragingOn();
m_shrink->SetInputConnection(reader->GetOutputPort());
m_shrink->Update();
ssss = m_shrink->GetOutput()->GetNumberOfPoints();

vtkSmartPointer<vtkImageDataGeometryFilter> geometry = vtkSmartPointer<vtkImageDataGeometryFilter>::New();

geometry->SetInputConnection(m_shrink->GetOutputPort());//结构点提取几何图形
geometry->Update();
ssss = geometry->GetOutput()->GetNumberOfPoints();

vtkPolyDataReader* myreader = vtkPolyDataReader::New();

vtkSmartPointer<vtkContourFilter> m_skinExtractor = vtkSmartPointer<vtkContourFilter>::New();//生成等值面/线

m_skinExtractor->SetInputConnection(m_shrink->GetOutputPort());
m_skinExtractor->SetValue(0, 2000);//调整阈值，400以上是骨组织
//	m_skinExtractor->SetValue(1, 800);//调整阈值，400以上是骨组织
//	m_skinExtractor->Update();
int qssss = m_skinExtractor->GetOutput()->GetNumberOfPoints();

vtkSmartPointer<vtkDecimatePro> m_deci = vtkSmartPointer<vtkDecimatePro>::New();//减少网格中三角形的数量

m_deci->SetTargetReduction(0.3);//减少到70%
m_deci->SetInputConnection(m_skinExtractor->GetOutputPort());
m_deci->Update();
vtkSmartPointer<vtkSmoothPolyDataFilter> m_smooth = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();//拉普拉斯平滑

m_smooth->SetInputConnection(m_deci->GetOutputPort());
m_smooth->SetNumberOfIterations(500);
m_smooth->Update();
vtkSmartPointer<vtkPolyDataNormals> m_skinNormals = vtkSmartPointer<vtkPolyDataNormals>::New();//计算多边形网格的法线

m_skinNormals->SetInputConnection(m_smooth->GetOutputPort());
m_skinNormals->SetComputeCellNormals(1);
m_skinNormals->SetComputePointNormals(1);
m_skinNormals->SetFeatureAngle(60.0);//设置定义的锐角
m_skinNormals->Update();

vtkSmartPointer<vtkStripper> m_stripper = vtkSmartPointer<vtkStripper>::New();//创造三角形条

m_stripper->SetInputConnection(m_skinNormals->GetOutputPort());
m_stripper->Update();

vtkSmartPointer<vtkTriangleFilter> m_triangle = vtkSmartPointer<vtkTriangleFilter>::New();//将多边形变成三角形条，消耗更少的内存
m_triangle->SetInputConnection(m_stripper->GetOutputPort());
m_triangle->Update();

// 		vtkSmartPointer<vtkPolyDataReader> reader22 =
// 			vtkSmartPointer<vtkPolyDataReader>::New();
// 		//reader->SetFileName("E:\\11.vtk");
// 		reader22->SetFileName("E:\\mridata22.vtk");
// 		reader22->Update();

// 		vtkSmartPointer<vtkMaskPoints> mask =
// 			vtkSmartPointer<vtkMaskPoints>::New();
// 		mask->SetInputConnection(reader22->GetOutputPort());
// 		mask->SetMaximumNumberOfPoints(10);
// 		mask->RandomModeOn();
// 		//	mask->GetOutput()->GetPointData()->SetVectors(myfl);
// 		mask->Update();



//	int qqrr = mask->GetOutput()->GetNumberOfPoints();

// 		my_writer->SetFileName("E:\\mridata22.vtk");
// 		my_writer->SetInputConnection(m_triangle->GetOutputPort());
// 		my_writer->Write();
// 		cout << "end" << endl;
// 		system("pause");

vtkSmartPointer<vtkCylinderSource> cylinder =

vtkSmartPointer<vtkCylinderSource>::New();

cylinder->SetHeight(2.0);

cylinder->SetRadius(1.0);

cylinder->SetResolution(10);

//cylinder->Update();

vtkSmartPointer<vtkArrowSource> m_arrow = vtkSmartPointer<vtkArrowSource>::New();
m_arrow->SetShaftRadius(0.03);
m_arrow->SetTipLength(0.35);

unsigned char red[3] = { 255, 0, 0 };
unsigned char blue[3] = { 0, 255, 0 };
unsigned char green[3] = { 0, 0, 255 };

vtkSmartPointer<vtkUnsignedCharArray> m_point = vtkSmartPointer<vtkUnsignedCharArray>::New();

m_point->SetNumberOfComponents(3);
m_point->InsertNextTypedTuple(red);
m_point->InsertNextTypedTuple(green);
m_point->InsertNextTypedTuple(blue);
m_point->InsertNextTypedTuple(green);
m_point->InsertNextTypedTuple(blue);

vtkSmartPointer<vtkPointData> ppdd = vtkSmartPointer<vtkPointData>::New();

vtkSmartPointer<vtkGlyph3D> glyph =
vtkSmartPointer<vtkGlyph3D>::New();
glyph->SetInputConnection(m_triangle->GetOutputPort());
glyph->SetSourceConnection(m_arrow->GetOutputPort());
glyph->ScalingOn();
glyph->SetScaleFactor(0.002);
glyph->OrientOn();
glyph->ClampingOff();
//	glyph->SetVectorModeToUseNormal();
glyph->SetVectorModeToUseVector();
//	glyh->SetScaleModeToScaleByScalar();
//	glyh->SetScaleModeToScaleByScalar();
glyph->SetColorModeToColorByVector();

vtkSmartPointer<vtkUnsignedCharArray> cellColors =
vtkSmartPointer<vtkUnsignedCharArray>::New();
cellColors->SetNumberOfComponents(3);
cellColors->InsertNextTupleValue(red);
cellColors->InsertNextTupleValue(green);

vtkSmartPointer<vtkLookupTable> m_table = vtkSmartPointer<vtkLookupTable>::New();
m_table->SetNumberOfColors(4);
m_table->SetTableValue(0, 1.0, 0, 0, 0);
m_table->SetTableValue(1, 0, 1.0, 0, 0);
m_table->SetTableValue(2, 0, 0, 1.0, 0);
m_table->SetTableValue(3, 0, 0, 0, 1.0);
//m_table->SetNumberOfColors(255);
m_table->Build();

//定义颜色映射表
vtkLookupTable *pColorTable = vtkLookupTable::New();
// 	pColorTable->SetNumberOfColors(6);
// 	pColorTable->SetTableValue(0, 0, 0, 0, 1.0);
//  	pColorTable->SetTableValue(-900, 0.0, 1.0, 1.0, 1.0);
//  	pColorTable->SetTableValue(900, 0.5, 1.0, 0.2, 0.7);
// 	pColorTable->SetTableValue(900, 1.0, 0.0, 1.0, 1.0);
// 	pColorTable->SetTableValue(1800, 0.0, 0.0, 1.0, 1.0);
// 	pColorTable->SetTableValue(5, 1.0, 1.0, 0.0, 1.0);
//	pColorTable->SetValueRange(0, 1);
//	pColorTable->SetSaturationRange(1, 1);
//	pColorTable->SetHueRange(0.4, 0.9);
pColorTable->SetHueRange(0.667, 0);
//pColorTable->SetAlphaRange(0.2, 0.8);

pColorTable->Build();


vtkSmartPointer<vtkPolyDataMapper> originMapper =
vtkSmartPointer<vtkPolyDataMapper>::New();
originMapper->SetInputConnection(glyph->GetOutputPort());
//originMapper->SetInputData(cube);
//originMapper->ScalarVisibilityOff();
originMapper->SetScalarRange(0,800);
originMapper->SetLookupTable(pColorTable);

vtkSmartPointer<vtkLookupTable> lut =
vtkSmartPointer<vtkLookupTable>::New();
lut->SetNumberOfTableValues(8);
lut->Build();
//lut->SetTableValue(0, 0, 0, 0, 1);
lut->SetTableValue(1, 0.8900, 0.8100, 0.3400, 1);
lut->SetTableValue(2, 1.0000, 0.3882, 0.2784, 1);
lut->SetTableValue(3, 0.9608, 0.8706, 0.7020, 1);
lut->SetTableValue(4, 0.9020, 0.9020, 0.9804, 1);
lut->SetTableValue(5, 1.0000, 0.4900, 0.2500, 1);
lut->SetTableValue(6, 0.5300, 0.1500, 0.3400, 1);
lut->SetTableValue(7, 0.9804, 0.5020, 0.4471, 1);


vtkSmartPointer<vtkActor> originActor =
vtkSmartPointer<vtkActor>::New();
originActor->SetMapper(originMapper);
originActor->GetProperty()->SetOpacity(0.3);

originActor->GetProperty()->SetColor(1, 0, 0);

vtkSmartPointer<vtkPolyDataMapper> glyphMapper =
vtkSmartPointer<vtkPolyDataMapper>::New();
glyphMapper->SetInputData(glyph->GetOutput());
//	glyphMapper->ScalarVisibilityOff();
//	glyphMapper->SetScalarRange(0,550);
//	glyphMapper->SetLookupTable(lut);

vtkSmartPointer<vtkActor> glyphActor =
vtkSmartPointer<vtkActor>::New();
glyphActor->SetMapper(glyphMapper);
//glyphActor->GetProperty()->SetColor(1, 0, 0);

vtkSmartPointer<vtkPolyDataMapper> myarrowmap = vtkSmartPointer<vtkPolyDataMapper>::New();
myarrowmap->SetInputConnection(m_stripper->GetOutputPort());

vtkSmartPointer<vtkActor> m_at2 = vtkSmartPointer<vtkActor>::New();
m_at2->SetMapper(myarrowmap);
m_at2->GetProperty()->SetColor(1, 0, 0);
vtkSmartPointer<vtkRenderer> glyphRenderer =
vtkSmartPointer<vtkRenderer>::New();
glyphRenderer->AddActor(originActor);


vtkSmartPointer<vtkRenderWindow> renderWindow =
vtkSmartPointer<vtkRenderWindow>::New();

renderWindow->AddRenderer(glyphRenderer);
renderWindow->SetSize(1280, 960);
renderWindow->Render();
renderWindow->SetWindowName("PolyDataNormal");

vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
vtkSmartPointer<vtkRenderWindowInteractor>::New();
renderWindowInteractor->SetRenderWindow(renderWindow);
renderWindowInteractor->Initialize();
renderWindowInteractor->Start();

return 0;

}
*/

#include "vtkPointSource.h"
#include "vtkHyperStreamline.h"
#include "vtkLineSource.h"

#include "vtkRungeKutta2.h"
#include "vtkRungeKutta45.h"

#include "vtkAssignAttribute.h"
#include "vtkScalarBarActor.h"

#include <iostream>

using namespace std;
#include <vtkSmartPointer.h>
//#include <vtkJPEGReader.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkAVIWriter.h>
#include<vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkImageViewer2.h>
#include <vtkCommand.h>
#include <vtkWindowToImageFilter.h>
#include "vtkStructuredGridAlgorithm.h"
#include "vtkUnsignedShortArray.h"
/*
int main()
{

vtkAssignAttribute* aa = vtkAssignAttribute::New();
vtkStructuredGrid* grid[25];

vtkStructuredGridAlgorithm* myread = vtkStructuredGridAlgorithm::New();
vtkPolyDataMapper* mymapper[25];

vtkSmartPointer<vtkStreamTracer> streamer[25];
vtkSmartPointer<vtkMaskPoints> mask;
vtkFloatArray* myscalar = vtkFloatArray::New();

vtkFloatArray* myscalarfake = vtkFloatArray::New();
vtkSmartPointer<vtkStructuredGridReader> struww[25];
vtkSmartPointer<vtkTubeFilter> streamtube[25];

myscalar->SetName("scalars");
int m_dem[3] = { 256, 256, 25 };
double mm_pp[3] = { 0 };
vtkPoints* m_po = vtkPoints::New();
m_po->SetDataTypeToUnsignedShort();
vtkFloatArray* vectors = vtkFloatArray::New();

vtkFloatArray* fake = vtkFloatArray::New();
fake->SetName("vectors");
fake->SetNumberOfComponents(3);
vectors->SetName("vectors");
vectors->SetNumberOfComponents(3);


//定义颜色映射表
vtkLookupTable *pColorTable = vtkLookupTable::New();
//		pColorTable->SetNumberOfColors(3);
pColorTable->SetTableValue(0, 0, 0.0, 1.0, 1.0);
pColorTable->SetTableValue(2, 0.117, 0.564, 1, 1.0);
pColorTable->SetTableValue(1, 0.3, 0.62, 1.0, 1.0);
pColorTable->SetTableValue(3, 1.0, 0.0, 0.0, 1.0);
pColorTable->SetTableValue(4, 1.0, 0.0, 0.0, 1.0);
pColorTable->SetTableValue(5, 1.0, 0.0, 0.0, 1.0);
// 		pColorTable->SetTableValue(6, 1.0, 0.0, 0.0, 1.0);
// 		pColorTable->SetTableValue(7, 1.0, 0.0, 0.0, 1.0);
pColorTable->SetValueRange(0, 500);
//		pColorTable->SetSaturationRange(1, 1);
//	pColorTable->SetHueRange(0.37, 2.0);//0.667
//	pColorTable->SetAlphaRange(1, 1);
//	pColorTable->SetValueRange(1, 1);
pColorTable->SetNumberOfTableValues(6);
pColorTable->SetAboveRangeColor(1, 0, 0, 1);
pColorTable->UseAboveRangeColorOn();
//pColorTable->SetAlphaRange(0.2, 0.8);

pColorTable->Build();

vtkSmartPointer<vtkRungeKutta4> Runge =
vtkSmartPointer<vtkRungeKutta4>::New();

for (int i = 0; i < 25; i++)
{
for (int j = 0; j < 256; j++)
{
for (int k = 0; k < 256; k++)
{
mm_pp[0] = k;
mm_pp[1] = j;
mm_pp[2] = i;
m_po->InsertNextPoint(mm_pp);
}
}
}

for (int m = 0; m < 1; m++)//25
{
string qq = "E:\\dataofdcm\\stream\\data" + to_string(m + 1) + ".dat";
std::ifstream readfile(qq, std::ios::binary);//dataofdcm\\

int  ch[3] = { 0 };
int asd = 0;

int line = 0;
while (!readfile.eof())
{

readfile.read((char*)(&ch[0]), sizeof(ch[0]));
if (readfile.eof())
{
break;
}
readfile.read((char*)(&ch[1]), sizeof(ch[1]));
if (readfile.eof())
{
break;
}
readfile.read((char*)(&ch[2]), sizeof(ch[2]));

if (readfile.eof())
{
break;
}

vectors->InsertTuple3(asd, -ch[1], ch[2], ch[0]);
//			fake->InsertTuple3(asd, ch[0], ch[1], ch[2]);
int mysqrt = sqrt(pow(ch[0], 2) + pow(ch[1], 2) + pow(ch[2], 2));
//		cout << mysqrt << endl;
myscalar->InsertTuple1(asd, mysqrt);
line++;
asd++;

}
cout << asd << endl;
readfile.close();
int vecnum = vectors->GetNumberOfTuples();

grid[m] = vtkStructuredGrid::New();
grid[m]->SetDimensions(m_dem);
grid[m]->SetPoints(m_po);
grid[m]->GetPointData()->SetScalars(myscalar);//颜色
grid[m]->GetPointData()->SetVectors(vectors);//流线

SYSTEMTIME sys_time, sys_time2;
GetLocalTime(&sys_time);

// 		vtkSmartPointer<vtkStructuredGridWriter> struww1 = vtkSmartPointer<vtkStructuredGridWriter>::New();
// 		struww1->SetInputData(grid[m]);
//
// 		struww1->SetFileTypeToBinary();
// 		struww1->SetFileName("E:\\testscalar.vtk");
//
// 		struww1->Update();
//
// 		struww1->Write();
// 	 	system("pause");

// 		struww[m] = vtkSmartPointer<vtkStructuredGridReader>::New();
// 		struww[m]->SetFileName("E:\\testscalar.vtk");//rysmall54321new
// 		struww[m]->Update();

cout << "write over" << endl;

GetLocalTime(&sys_time2);
//		cout << "second:" << sys_time2.wSecond - sys_time.wSecond << "millsec:" << sys_time2.wMilliseconds - sys_time.wSecond << endl;

//		system("pause");

if (m == 0)
{
mask = vtkSmartPointer<vtkMaskPoints>::New();
//	mask->SetInputConnection(struww->GetOutputPort());
mask->SetInputData(grid[0]);
mask->SetMaximumNumberOfPoints(2000);
mask->RandomModeOn();
mask->Update();
}

vtkStructuredGrid* grid22 = vtkStructuredGrid::New();

// 		grid22 = struww[m]->GetOutput();
// 		int gghhjj = grid22->GetNumberOfPoints();
//
// 		grid22->GetPointData()->SetVectors(fake);
// 		grid22->GetPointData()->SetScalars(myscalar);
// 		grid22->GetPointData()->Update();

streamer[m] = vtkSmartPointer<vtkStreamTracer>::New();
streamer[m]->SetInputData(grid[m]);
//		streamer[m]->SetInputData(grid[m]);
streamer[m]->SetSourceConnection(mask->GetOutputPort());
//		streamer->SetStartPosition(1, 1, 1);//108 254.156 48 12		7.476 254 48 131.471 254 48 //0.1, 2.1, 0.5
streamer[m]->SetMaximumPropagation(500);
streamer[m]->SetInitialIntegrationStep(0.05);
//		streamer[m]->SetInputArrayToProcess(1, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, vtkDataSetAttributes::VECTORS);
streamer[m]->SetIntegrationDirection(vtkStreamTracer::BOTH);
streamer[m]->SetIntegrator(Runge);
streamer[m]->Update();			//属性不全

streamtube[m] = vtkSmartPointer<vtkTubeFilter>::New();
streamtube[m]->SetInputData(streamer[m]->GetOutput());
streamtube[m]->SetInputArrayToProcess(1, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, vtkDataSetAttributes::VECTORS);
streamtube[m]->SetRadius(0.2);
streamtube[m]->SetNumberOfSides(12);
streamtube[m]->SetVaryRadiusToVaryRadiusByVector();
streamtube[m]->Update();

vectors->Delete();
m_po->Delete();
myscalar->Delete();


mymapper[m] = vtkPolyDataMapper::New();

mymapper[m]->SetInputConnection(streamtube[0]->GetOutputPort());

mymapper[m]->SetScalarRange(0, 500);
mymapper[m]->SetLookupTable(pColorTable);
mymapper[m]->SetScalarModeToUsePointData();
//	mymapper->SelectColorArray("scalars");
mymapper[m]->SetColorModeToMapScalars();
//	mymapper[m]->Update();
}



//*********************渲染************************
vtkSmartPointer<vtkActor> streamActor =
vtkSmartPointer<vtkActor>::New();
streamActor->GetProperty()->SetColor(1, 1, 1);

vtkSmartPointer<vtkScalarBarActor> scalarBar =
vtkSmartPointer<vtkScalarBarActor>::New();
scalarBar->SetTitle("vectors");
scalarBar->SetNumberOfLabels(4);
scalarBar->SetLookupTable(mymapper[0]->GetLookupTable());

vtkSmartPointer<vtkRenderer> glyphRenderer =
vtkSmartPointer<vtkRenderer>::New();
glyphRenderer->AddActor(streamActor);
glyphRenderer->AddActor2D(scalarBar);
//	glyphRenderer->AddActor(glyphActor);

vtkSmartPointer<vtkRenderWindow> renderWindow =
vtkSmartPointer<vtkRenderWindow>::New();
renderWindow->AddRenderer(glyphRenderer);
renderWindow->SetSize(1500, 1200);

renderWindow->SetWindowName("PolyDataNormal");

vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
vtkSmartPointer<vtkRenderWindowInteractor>::New();
renderWindowInteractor->SetRenderWindow(renderWindow);
renderWindowInteractor->Initialize();

//	scalarBar->SetTitle(streamtube[0]->GetOutput()->GetPointData()->GetScalars()->GetName());


// 	vtkSmartPointer<vtkDataSetMapper> dataMapper =
// 		vtkSmartPointer<vtkDataSetMapper>::New();
// 	dataMapper->SetInputConnection(streamer[0]->GetOutputPort());
// 	//	dataMapper->SetInputData(grid[0]);
// 	dataMapper->ScalarVisibilityOff();
// 	dataMapper->SetLookupTable(pColorTable);
// 	dataMapper->SetScalarModeToUsePointData();
// 	dataMapper->SetColorModeToMapScalars();
// //	dataMapper->SetUseLookupTableScalarRange(0);
// 	dataMapper->SetScalarVisibility(1);
// 	dataMapper->Update();


//	streamActor->SetMapper(mymapper[0]);


//	renderWindowInteractor->Start();
//	renderWindow->Render();
// 		vtkSmartPointer<vtkAVIWriter> writer = vtkSmartPointer<vtkAVIWriter>::New();
//
// 		vtkSmartPointer<vtkWindowToImageFilter> filter = vtkSmartPointer<vtkWindowToImageFilter>::New();
// 		filter->SetInput(renderWindow);
// 		writer->SetInputConnection(filter->GetOutputPort());
// 		writer->SetFileName("test2.avi");
// 		writer->Start();

for (size_t i = 1; i < 25; i++)
{

//				mymapper->SetInputConnection(streamtube[i]->GetOutputPort());
mymapper[i]->Update();
//	streamActor->SetMapper(mymapper[i]);
renderWindow->Render();
Sleep(100);
// // 		for (int i = 1; i < 10; i++)
// // 		{
// // 			filter->Modified();
// // 			writer->Write();
// // 		}
//
}

//		writer->End();


return 0;

}
*/

#include "vtkBMPWriter.h"

/*******************************************显示流线************************************/
/*
int main()
{

vtkAssignAttribute* aa = vtkAssignAttribute::New();
vtkStructuredGrid* grid[25];

vtkStructuredGridAlgorithm* myread = vtkStructuredGridAlgorithm::New();
vtkPolyDataMapper* mymapper;

vtkSmartPointer<vtkStreamTracer> streamer[25];
vtkSmartPointer<vtkMaskPoints> mask;
vtkFloatArray* myscalar = vtkFloatArray::New();

vtkDICOMImageReader* reader = vtkDICOMImageReader::New();
reader->SetDirectoryName("E:\\dataofdcm\\mydata\\onetime");

reader->SetDataScalarTypeToUnsignedShort();
reader->SetDataSpacing(1, 1, 1);
reader->SetDataByteOrderToLittleEndian();
reader->Update();

vtkFloatArray* myscalarfake = vtkFloatArray::New();
vtkSmartPointer<vtkStructuredGridReader> struww[25];
vtkSmartPointer<vtkTubeFilter> streamtube[25];

myscalar->SetName("scalars");
int m_dem[3] = { 84, 256, 256 };//
double mm_pp[3] = { 0 };
vtkPoints* m_po = vtkPoints::New();
m_po->SetDataTypeToUnsignedShort();
vtkFloatArray* vectors = vtkFloatArray::New();

vtkFloatArray* fake = vtkFloatArray::New();
fake->SetName("vectors");
fake->SetNumberOfComponents(3);
vectors->SetName("vectors");
vectors->SetNumberOfComponents(3);


//定义颜色映射表
vtkLookupTable *pColorTable = vtkLookupTable::New();
//		pColorTable->SetNumberOfColors(3);
// pColorTable->SetTableValue(0, 0, 0.0, 1.0, 1.0);
// pColorTable->SetTableValue(2, 0.117, 0.564, 1, 1.0);
// pColorTable->SetTableValue(1, 0.3, 0.62, 1.0, 1.0);
// pColorTable->SetTableValue(3, 1.0, 0.0, 0.0, 1.0);
// pColorTable->SetTableValue(4, 1.0, 0.0, 0.0, 1.0);
// pColorTable->SetTableValue(5, 1.0, 0.0, 0.0, 1.0);
// 		pColorTable->SetTableValue(6, 1.0, 0.0, 0.0, 1.0);
// 		pColorTable->SetTableValue(7, 1.0, 0.0, 0.0, 1.0);
//pColorTable->SetValueRange(0, 1000);
//		pColorTable->SetSaturationRange(1, 1);
	pColorTable->SetHueRange(0.667, 0);//0.667
//	pColorTable->SetAlphaRange(1, 1);
//	pColorTable->SetValueRange(1, 1);
// pColorTable->SetNumberOfTableValues(6);
// pColorTable->SetAboveRangeColor(1, 0, 0, 1);
// pColorTable->UseAboveRangeColorOn();
//pColorTable->SetAlphaRange(0.2, 0.8);

pColorTable->Build();

vtkSmartPointer<vtkRungeKutta4> Runge =
vtkSmartPointer<vtkRungeKutta4>::New();

for (int i = 0; i < 256; i++)//25
{
for (int j = 0; j < 256; j++)
{
for (int k = 0; k < 84; k++)
{
mm_pp[0] = k;
mm_pp[1] = j;
mm_pp[2] = i;
m_po->InsertNextPoint(mm_pp);
}
}
}

for (int m = 0; m < 1; m++)//25
{
clock_t start, finish;

start = clock();

// 		string qq = "E:\\dataofdcm\\stream\\data" + to_string(m + 1) + ".dat";
// string qq = "E:\\testdat\\Data1.dat";
// std::ifstream readfile(qq, std::ios::binary);//dataofdcm
// 
// int  ch[3] = { 0 };
// int asd = 0;
// 
// readfile.read((char*)(&ch[0]), sizeof(ch[0]));
// 
// 
// while (!readfile.eof())
// {
// 
// readfile.read((char*)(&ch[0]), sizeof(ch[0]));
// if (readfile.eof())
// {
// break;
// }
// readfile.read((char*)(&ch[1]), sizeof(ch[1]));
// if (readfile.eof())
// {
// break;
// }
// readfile.read((char*)(&ch[2]), sizeof(ch[2]));
// 
// if (readfile.eof())
// {
// break;
// }
// 
// vectors->InsertTuple3(asd, -ch[1], ch[2], ch[0]);
// int mysqrt = sqrt(pow(ch[0], 2) + pow(ch[1], 2) + pow(ch[2], 2));
// myscalar->InsertTuple1(asd, mysqrt);
// asd++;
// 
// }
//readfile.close();
string csPathName = "E:\\testdat\\Data1.dat";

WIN32_FIND_DATA fileInfo;
HANDLE hFind;
DWORD fileSize;
hFind = FindFirstFile(csPathName.c_str(), &fileInfo);
if (hFind != INVALID_HANDLE_VALUE)		fileSize = fileInfo.nFileSizeLow;	//得到数据文件大小。
FindClose(hFind);
FILE * file;
if ((file = fopen(csPathName.c_str(), "rt")) == NULL)		return false;			//
char	filedata[500];
int		idata, jdata;
fscanf(file, "%s", filedata);											//（获得首个字符串）
if (strcmp(filedata, "TITLE"))		return false;						//if not tecplot file.，比较字符串

//打开PTV结果。。。。。。
DWORD lopnumber, lopstart;
int mi, mj, mk;
while (strcmp(filedata, "DOUBLE)"))
{
	fscanf(file, "%s", filedata);
}
int x = 0, y = 0, z = 0;
double  u = 0, v = 0, w = 0;

for (size_t i = 0; i < 256 * 256 * 84; i++)
{
	fscanf(file, "%d\t%d\t%d\t%lf\t%lf\t%lf\t", &x, &y, &z, &u, &v, &w);
	 vectors->InsertTuple3(i, -v, w, u);
	 int mysqrt = sqrt(pow(u, 2) + pow(v, 2) + pow(w, 2));
	 myscalar->InsertTuple1(i, mysqrt);
	 if (x == 20 && y == 55 & z == 134)
	 {
		 cout <<" "<< endl;
	 }
}

fclose(file);

finish = clock();

cout << ((double)(finish - start) / CLOCKS_PER_SEC) << endl;

int vecnum = vectors->GetNumberOfTuples();

grid[m] = vtkStructuredGrid::New();
grid[m]->SetDimensions(m_dem);
grid[m]->SetPoints(m_po);
grid[m]->GetPointData()->SetScalars(myscalar);//颜色
grid[m]->GetPointData()->SetVectors(vectors);//流线

if (m == 0)
{
mask = vtkSmartPointer<vtkMaskPoints>::New();
//	mask->SetInputConnection(struww->GetOutputPort());
mask->SetInputData(grid[0]);
mask->SetMaximumNumberOfPoints(4000);
mask->RandomModeOn();
mask->Update();
}

vtkPointSource* seeds = vtkPointSource::New();
seeds->SetRadius(30);
seeds->SetCenter(40, 58, 134);
seeds->SetNumberOfPoints(1000);
seeds->Update();

int qqqq = seeds->GetOutput()->GetNumberOfPoints();

streamer[m] = vtkSmartPointer<vtkStreamTracer>::New();
streamer[m]->SetInputData(grid[m]);
//streamer[m]->SetSourceConnection(mask->GetOutputPort());
streamer[m]->SetSourceConnection(seeds->GetOutputPort());
//streamer[m]->SetStartPosition(40, 58, 134);//108 254.156 48 12		7.476 254 48 131.471 254 48 //0.1, 2.1, 0.5
streamer[m]->SetMaximumPropagation(500);
streamer[m]->SetInitialIntegrationStep(0.05);
//		streamer[m]->SetInputArrayToProcess(1, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, vtkDataSetAttributes::VECTORS);
streamer[m]->SetIntegrationDirection(vtkStreamTracer::BOTH);
streamer[m]->SetIntegrator(Runge);
//		streamer[m]->Update();			//属性不全

streamtube[m] = vtkSmartPointer<vtkTubeFilter>::New();
streamtube[m]->SetInputConnection(streamer[m]->GetOutputPort());
streamtube[m]->SetInputArrayToProcess(1, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, vtkDataSetAttributes::VECTORS);
streamtube[m]->SetRadius(0.2);
streamtube[m]->SetNumberOfSides(6);
streamtube[m]->SetVaryRadiusToVaryRadiusByScalar();
streamtube[m]->Update();

vectors->Delete();
m_po->Delete();
myscalar->Delete();

}

mymapper = vtkPolyDataMapper::New();

mymapper->SetInputConnection(streamtube[0]->GetOutputPort());

mymapper->SetScalarRange(0, 500);
mymapper->SetLookupTable(pColorTable);
mymapper->SetScalarModeToUsePointData();
mymapper->SetColorModeToMapScalars();
//	mymapper->Update();


//*********************渲染**************************
vtkSmartPointer<vtkActor> streamActor =
vtkSmartPointer<vtkActor>::New();
streamActor->SetMapper(mymapper);
streamActor->GetProperty()->SetColor(1, 1, 1);

vtkSmartPointer<vtkScalarBarActor> scalarBar =
vtkSmartPointer<vtkScalarBarActor>::New();
scalarBar->SetTitle("vectors");
scalarBar->SetNumberOfLabels(4);
scalarBar->SetLookupTable(mymapper->GetLookupTable());

vtkSmartPointer<vtkRenderer> glyphRenderer =
vtkSmartPointer<vtkRenderer>::New();
glyphRenderer->AddActor(streamActor);
glyphRenderer->AddActor2D(scalarBar);
//	glyphRenderer->AddActor(glyphActor);

vtkSmartPointer<vtkRenderWindow> renderWindow =
vtkSmartPointer<vtkRenderWindow>::New();
renderWindow->AddRenderer(glyphRenderer);
renderWindow->SetSize(1500, 1200);
renderWindow->Render();
renderWindow->SetWindowName("PolyDataNormal");

vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
vtkSmartPointer<vtkRenderWindowInteractor>::New();
renderWindowInteractor->SetRenderWindow(renderWindow);
renderWindowInteractor->Initialize();
renderWindowInteractor->Start();

system("pause");

vtkSmartPointer<vtkAVIWriter> writer = vtkSmartPointer<vtkAVIWriter>::New();
vtkSmartPointer<vtkBMPWriter> bmpwriter = vtkSmartPointer<vtkBMPWriter>::New();

vtkSmartPointer<vtkWindowToImageFilter> filter = vtkSmartPointer<vtkWindowToImageFilter>::New();
filter->SetInput(renderWindow);
bmpwriter->SetInputConnection(filter->GetOutputPort());

//	writer->SetInputConnection(filter->GetOutputPort());
//	writer->SetFileName("test2.avi");
//	writer->Start();

for (size_t i = 0; i < 25; i++)
{

mymapper->SetInputConnection(streamtube[i]->GetOutputPort());
mymapper->Update();
//		streamActor->SetMapper(mymapper);
renderWindow->Render();
Sleep(400);
// 		for (int i = 1; i < 25; i++)
// 		{
// 			filter->Modified();
// 			writer->Write();
// 		}
//		string mypicname = "pic" + to_string(i) + ".bmp";
//		bmpwriter->SetFileName(mypicname.c_str());
// 		filter->Modified();
// 		bmpwriter->Write();

}

//	writer->End();

return 0;
}
*/


#include "vtkAnimationCue.h"
#include "vtkAnimationScene.h"

#include "vtkSurfaceReconstructionFilter.h"

#include "vtkVertexGlyphFilter.h"

#include "vtkStringArray.h"

#include "itkImageSeriesReader.h"

#include "vtkPlaybackWidget.h"
#include "vtkPlaybackRepresentation.h"
#include "vtkStringArray.h"
#include "vtkStdString.h"
#include "vtkImageAppend.h"




class vtkCustomAnimationCue : public vtkAnimationCue
{
public:
	static vtkCustomAnimationCue* New();
	int vtkTypeRevisionMacro(vtkCustomAnimationCue, vtkAnimationCue);

	vtkRenderWindow *RenWin;
	vtkSphereSource *Sphere;

protected:
	vtkCustomAnimationCue()
	{
		this->RenWin = 0;
		this->Sphere = 0;
	}

	// Overridden to adjust the sphere'sradius depending on the frame we  
	// are rendering. In this animation wewant to change the StartTheta  
	// of the sphere from 0 to 180 over thelength of the cue.  
	virtual void TickInternal(double currenttime, double deltatime, double clocktime)
	{
		double new_st = currenttime * 180;
		// since the cue is in normalizedmode, the currenttime will be in the  
		// range[0,1], where 0 is start ofthe cue and 1 is end of the cue.  
		this->Sphere->SetStartTheta(new_st);
		this->RenWin->Render();
	}
};
vtkStandardNewMacro(vtkCustomAnimationCue);
//int vtkCxxRevisionMacro(vtkCustomAnimationCue, "$Revision$");
/*
int main(int argc, char *argv[])
{
// Create the graphics sturctures. Therenderer renders into the
// render window.
vtkRenderer *ren1 = vtkRenderer::New();
vtkRenderWindow *renWin = vtkRenderWindow::New();
renWin->SetMultiSamples(0);
renWin->AddRenderer(ren1);

vtkSphereSource *sphere = vtkSphereSource::New();
vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
mapper->SetInputConnection(sphere->GetOutputPort());
vtkActor *actor = vtkActor::New();
actor->SetMapper(mapper);
ren1->AddActor(actor);

ren1->ResetCamera();
renWin->Render();

//Create an Animation Scene
vtkAnimationScene *scene = vtkAnimationScene::New();
scene->SetModeToSequence();
scene->SetFrameRate(30);
scene->SetStartTime(0);
scene->SetEndTime(60);

// Create an Animation Cue to animate thecamera.
vtkCustomAnimationCue *cue1 = vtkCustomAnimationCue::New();
cue1->Sphere = sphere;
cue1->RenWin = renWin;
cue1->SetTimeModeToNormalized();
cue1->SetStartTime(0);
cue1->SetEndTime(1.0);
scene->AddCue(cue1);
scene->Play();
scene->Stop();

ren1->Delete();
renWin->Delete();
scene->Delete();
cue1->Delete();
return 0;
}

*/


#include <iostream>

using namespace std;
#include <vtkSmartPointer.h>
//#include <vtkJPEGReader.h>


// int main()
// {
// vtkSmartPointer<vtkImageCanvasSource2D> source = vtkSmartPointer<vtkImageCanvasSource2D>::New();
// source->SetScalarTypeToUnsignedChar();
// source->SetNumberOfScalarComponents(3);
// source->SetExtent(0, 250, 0, 150, 0, 0);
// 
// vtkSmartPointer<vtkAVIWriter> writer = vtkSmartPointer<vtkAVIWriter>::New();
// vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
// vtkSmartPointer<vtkImageViewer2>imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
// imageViewer->SetInputConnection(source->GetOutputPort());
// imageViewer->SetupInteractor(iren);
// imageViewer->GetRenderer()->ResetCamera();
// imageViewer->GetRenderer()->SetBackground(1, 1, 1);
// 
// imageViewer->SetSize(800, 600);
// iren->Initialize();
// //    iren->Start();
// vtkSmartPointer<vtkWindowToImageFilter> filter = vtkSmartPointer<vtkWindowToImageFilter>::New();
// filter->SetInput(imageViewer->GetRenderWindow());
// writer->SetInputConnection(filter->GetOutputPort());
// writer->SetFileName("test4.avi");
// writer->Start();
// 
// for (unsigned int i = 0; i < 250; i++)
// {
// source->SetDrawColor(0, 0, 0, 1); //black
// source->FillBox(0, 300, 0, 300); //clear image
// source->SetDrawColor(255, 0, 0, 1); //red
// source->FillBox(i, 230, 80, 100);
// source->Update();
// imageViewer->Render();
// for (int i = 0; i < 5; i++)
// {
// filter->Modified();
// writer->Write();
// }
// 
// }
// writer->End();
// iren->Start();
// return 0;
// }


#include "vtkFixedPointVolumeRayCastMapper.h"
#include "vtkVolumeRayCastIsosurfaceFunction.h"
#include "vtkVolumeRayCastCompositeFunction.h"
#include "vtkPolyDataConnectivityFilter.h"
#include "vtkVolumeTextureMapper2D.h"
#include "vtkVolumeTextureMapper3D.h"

#include "vtkLODProp3D.h"

/*****************************体绘制********************************/
/*
int main()
{

vtkRenderWindowInteractor* renderWindowInteractor =
vtkRenderWindowInteractor::New();
vtkDICOMImageReader* reader = vtkDICOMImageReader::New();
reader->SetDataByteOrderToLittleEndian();
//reader->SetDirectoryName("E:\\Release\\LHYSE9"); //E:\dataofdcm\mydata\onetime
//E:\dataofdcm\cylinderstream
reader->SetDirectoryName("E:\\dataofdcm\\cylinderstream");
reader->SetDataScalarTypeToUnsignedShort();
reader->SetDataSpacing(1, 1, 1);
reader->SetDataByteOrderToLittleEndian();
//reader->Update();


vtkImageShiftScale *shiftScale = vtkImageShiftScale::New();
shiftScale->SetInputConnection(reader->GetOutputPort());
shiftScale->SetOutputScalarTypeToUnsignedChar();


vtkPolyDataConnectivityFilter* m_ConnectivityFilter = vtkPolyDataConnectivityFilter::New();
m_ConnectivityFilter->SetProgressText("m_ConnectivityFilter");
m_ConnectivityFilter->SetInputConnection(reader->GetOutputPort());
m_ConnectivityFilter->SetExtractionModeToLargestRegion();


//vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();

//vtkVolumeRayCastMapper* volumeMapper = vtkVolumeRayCastMapper::New();

vtkGPUVolumeRayCastMapper* highvolumeMapper = vtkGPUVolumeRayCastMapper::New();


vtkGPUVolumeRayCastMapper* volumeMapper = vtkGPUVolumeRayCastMapper::New();


 volumeMapper->SetAutoAdjustSampleDistances(0);
 volumeMapper->SetSampleDistance(0.5);


 volumeMapper->SetInputConnection(reader->GetOutputPort());

 highvolumeMapper->SetInputConnection(reader->GetOutputPort());
 highvolumeMapper->SetAutoAdjustSampleDistances(0);
 highvolumeMapper->SetSampleDistance(4 * highvolumeMapper->GetSampleDistance());


vtkVolumeRayCastCompositeFunction* composfunc = vtkVolumeRayCastCompositeFunction::New();
composfunc->SetCompositeMethodToInterpolateFirst();

vtkVolumeRayCastIsosurfaceFunction*rayfacefunc = vtkVolumeRayCastIsosurfaceFunction::New();

rayfacefunc->SetIsoValue(200);

//volumeMapper->SetVolumeRayCastFunction(composfunc);


vtkSmartPointer<vtkVolumeProperty> volumeProperty =
vtkSmartPointer<vtkVolumeProperty>::New();
volumeProperty->SetInterpolationTypeToLinear();
volumeProperty->ShadeOn();  //打开或者关闭阴影测试
volumeProperty->SetAmbient(0.4);		//环境光，数值大，阴影效果不明显
volumeProperty->SetDiffuse(0.6);  //散射光，数值大，显示效果粗糙
volumeProperty->SetSpecular(0.2); //反射光，数值大，显示效果光滑
//设置不透明度
vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity =
vtkSmartPointer<vtkPiecewiseFunction>::New();
compositeOpacity->AddPoint(70, 0.00);
compositeOpacity->AddPoint(90, 0.40);
compositeOpacity->AddPoint(180, 0.60);
compositeOpacity->AddPoint(400, 0.0);
volumeProperty->SetScalarOpacity(compositeOpacity); //设置不透明度传输函数
//compositeOpacity->AddPoint(120,  0.00);//测试隐藏部分数据,对比不同的设置
//compositeOpacity->AddPoint(180,  0.60);
//volumeProperty->SetScalarOpacity(compositeOpacity);

//设置颜色属性
vtkSmartPointer<vtkColorTransferFunction> color =
vtkSmartPointer<vtkColorTransferFunction>::New();
color->AddRGBPoint(0.000, 0.00, 0.00, 0.00);
color->AddRGBPoint(64.00, 1.00, 0.0, 0.00);
color->AddRGBPoint(190.0, 1.00, 0.5, 0.7);
color->AddRGBPoint(400, 1, 1, 1);
volumeProperty->SetColor(color);

vtkSmartPointer<vtkVolume> volume =
vtkSmartPointer<vtkVolume>::New();
volume->SetMapper(volumeMapper);
volume->SetProperty(volumeProperty);

vtkLODProp3D* prop = vtkLODProp3D::New();
prop->AddLOD(volumeMapper, volumeProperty, 1);
prop->AddLOD(highvolumeMapper, volumeProperty, 2);


vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
ren->SetBackground(0, 1, 0);
ren->AddVolume(volume);//volume

vtkSmartPointer<vtkRenderWindow> rw = vtkSmartPointer<vtkRenderWindow>::New();
rw->AddRenderer(ren);
rw->SetSize(1200, 800);
rw->Render();
rw->SetWindowName("VolumeRendering PipeLine");


renderWindowInteractor->SetRenderWindow(rw);

ren->ResetCamera();
renderWindowInteractor->Initialize();
renderWindowInteractor->Start();

return EXIT_SUCCESS;

}
*/



/*****************************面绘制********************************/

#include "vtkTransform.h"

#include "vtkTransformPolyDataFilter.h"

int main()
{

vtkSmartPointer<vtkPolyDataWriter> my_writer = vtkSmartPointer<vtkPolyDataWriter>::New();
vtkSmartPointer< vtkDICOMImageReader > reader = vtkSmartPointer< vtkDICOMImageReader >::New();
// reader->SetDirectoryName("E:\\SE33");
//	reader->SetDirectoryName("E:\\SE2");//E:\dataofdcm\mydata\d0
//reader->SetDirectoryName("E:\\dataofdcm\\mymydcm");//cylinderstream
reader->SetDirectoryName("E:\\dataofdcm\\cylinderstream");
vtkStringArray* myarray = vtkStringArray::New();


// for (size_t i = 0; i < 10; i++)
// {
// 	string qqqq;
// 	qqqq = "E:\\SE33\\Z" + std::to_string(i+1)+".dcm";
// 	myarray->InsertNextValue(qqqq);
// }
// 
// 
// reader->SetFileNames(myarray);

vtkImageAppend* append = vtkImageAppend::New();
append->SetAppendAxis(2);


// char fileName[128];
//  for (int i = 1; i < 200; i++) //几个图像就循环几次  
//  {
// string qwewq = "E:/Release/LHYSE9/IM" + std::to_string(i);
// reader->SetFileName(qwewq.c_str());
// append->AddInputConnection(reader->GetOutputPort());
//  }

reader->SetDataScalarTypeToUnsignedShort();
reader->SetDataSpacing(1, 1, 1);
reader->SetDataByteOrderToLittleEndian();
reader->Update();

vtkSmartPointer<vtkImageShiftScale> ShiftScale =
vtkSmartPointer<vtkImageShiftScale>::New();
ShiftScale->SetInputConnection(reader->GetOutputPort());
ShiftScale->SetOutputScalarTypeToUnsignedInt();
ShiftScale->SetShift(1);
ShiftScale->SetScale(1000);
ShiftScale->Update();


vtkSmartPointer<vtkImageShrink3D> m_shrink = vtkSmartPointer<vtkImageShrink3D>::New();//二次抽样

m_shrink->SetShrinkFactors(0, 0, 0);//调节绘制图像的精细程度
m_shrink->AveragingOn();
m_shrink->SetInputConnection(reader->GetOutputPort());
m_shrink->Update();


// vtkSmartPointer<vtkImageDataGeometryFilter> geometry = vtkSmartPointer<vtkImageDataGeometryFilter>::New();
// 
// geometry->SetInputConnection(m_shrink->GetOutputPort());//结构点提取几何图形
// geometry->Update();

vtkSmartPointer<vtkContourFilter> m_skinExtractor = vtkSmartPointer<vtkContourFilter>::New();//生成等值面/线

m_skinExtractor->SetInputConnection(m_shrink->GetOutputPort());
m_skinExtractor->SetValue(0, 2000);//调整阈值，400以上是骨组织
//m_skinExtractor->SetValue(1, 800);//调整阈值，400以上是骨组织
m_skinExtractor->Update();

vtkSmartPointer<vtkDecimatePro> m_deci = vtkSmartPointer<vtkDecimatePro>::New();//减少网格中三角形的数量

m_deci->SetTargetReduction(0.3);//减少到70%
m_deci->SetInputConnection(m_skinExtractor->GetOutputPort());
m_deci->Update();
vtkSmartPointer<vtkSmoothPolyDataFilter> m_smooth = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();//拉普拉斯平滑

m_smooth->SetInputConnection(m_deci->GetOutputPort());
m_smooth->SetNumberOfIterations(500);
m_smooth->Update();
vtkSmartPointer<vtkPolyDataNormals> m_skinNormals = vtkSmartPointer<vtkPolyDataNormals>::New();//计算多边形网格的法线

m_skinNormals->SetInputConnection(m_smooth->GetOutputPort());
m_skinNormals->SetComputeCellNormals(1);
m_skinNormals->SetComputePointNormals(1);
m_skinNormals->SetFeatureAngle(60.0);//设置定义的锐角
m_skinNormals->Update();

vtkSmartPointer<vtkStripper> m_stripper = vtkSmartPointer<vtkStripper>::New();//创造三角形条

m_stripper->SetInputConnection(m_skinNormals->GetOutputPort());
m_stripper->Update();

vtkSmartPointer<vtkTriangleFilter> m_triangle = vtkSmartPointer<vtkTriangleFilter>::New();//将多边形变成三角形条，消耗更少的内存
m_triangle->SetInputConnection(m_stripper->GetOutputPort());
m_triangle->Update();

vtkSmartPointer<vtkTransform> pTransform = vtkSmartPointer<vtkTransform>::New();//翻转poly数据
//pTransform->RotateX(90);//x轴旋转90度
pTransform->RotateY(180);//z轴旋转180度
vtkSmartPointer<vtkTransformPolyDataFilter> pTransformPolyDataFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
pTransformPolyDataFilter->SetInputConnection(m_triangle->GetOutputPort());
pTransformPolyDataFilter->SetTransform(pTransform);
pTransformPolyDataFilter->Update();


vtkPolyDataConnectivityFilter* ConnectivityFilter = vtkPolyDataConnectivityFilter::New();
ConnectivityFilter->SetInputConnection(m_triangle->GetOutputPort());
ConnectivityFilter->SetExtractionModeToLargestRegion();
//ConnectivityFilter->Update();

int qqqqqq = ConnectivityFilter->GetNumberOfExtractedRegions();


//cout << qqqqqq << endl;

//定义颜色映射表
vtkLookupTable *pColorTable = vtkLookupTable::New();
// 	pColorTable->SetNumberOfColors(6);
// 	pColorTable->SetTableValue(0, 0, 0, 0, 1.0);
//  	pColorTable->SetTableValue(-900, 0.0, 1.0, 1.0, 1.0);
//  	pColorTable->SetTableValue(900, 0.5, 1.0, 0.2, 0.7);
// 	pColorTable->SetTableValue(900, 1.0, 0.0, 1.0, 1.0);
// 	pColorTable->SetTableValue(1800, 0.0, 0.0, 1.0, 1.0);
// 	pColorTable->SetTableValue(5, 1.0, 1.0, 0.0, 1.0);
//	pColorTable->SetValueRange(0, 1);
//	pColorTable->SetSaturationRange(1, 1);
//	pColorTable->SetHueRange(0.4, 0.9);
pColorTable->SetHueRange(0.667, 0);
//pColorTable->SetAlphaRange(0.2, 0.8);

pColorTable->Build();

vtkSmartPointer<vtkProperty> polyProperty =
vtkSmartPointer<vtkProperty>::New();
//volumeProperty->SetInterpolationTypeToLinear();
//volumeProperty->ShadeOn();  //打开或者关闭阴影测试
polyProperty->SetAmbient(0.4);		//环境光，数值大，阴影效果不明显
polyProperty->SetDiffuse(0.6);  //散射光，数值大，显示效果粗糙
polyProperty->SetSpecular(0.2); //反射光，数值大，显示效果光滑
//设置不透明度


vtkSmartPointer<vtkPolyDataMapper> originMapper =
vtkSmartPointer<vtkPolyDataMapper>::New();
originMapper->SetInputConnection(m_triangle->GetOutputPort());
//originMapper->SetInputData(cube);
//originMapper->ScalarVisibilityOff();
// originMapper->SetScalarRange(0,800);
// originMapper->SetLookupTable(pColorTable);


vtkSmartPointer<vtkActor> originActor =
vtkSmartPointer<vtkActor>::New();
originActor->SetMapper(originMapper);
//originActor->GetProperty()->SetOpacity(0.3);
originActor->GetProperty()->SetColor(1, 0, 0);
originActor->SetProperty(polyProperty);


vtkSmartPointer<vtkRenderer> glyphRenderer =
vtkSmartPointer<vtkRenderer>::New();
glyphRenderer->AddActor(originActor);
glyphRenderer->SetBackground(1, 1, 1);

vtkSmartPointer<vtkRenderWindow> renderWindow =
vtkSmartPointer<vtkRenderWindow>::New();

renderWindow->AddRenderer(glyphRenderer);
renderWindow->SetSize(1280, 960);
renderWindow->Render();
renderWindow->SetWindowName("PolyDataNormal");

vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
vtkSmartPointer<vtkRenderWindowInteractor>::New();
renderWindowInteractor->SetRenderWindow(renderWindow);

vtkPlaybackRepresentation* Representation = vtkPlaybackRepresentation::New();


vtkPlaybackWidget* PlaybackWidget = vtkPlaybackWidget::New();
PlaybackWidget->SetInteractor(renderWindowInteractor);
PlaybackWidget->SetRepresentation(Representation);


renderWindowInteractor->Initialize();
PlaybackWidget->On();
renderWindow->Render();
renderWindowInteractor->Start();


return 0;

}



/*
int main()
{
	vtkLookupTable *pColorTable = vtkLookupTable::New();

	//	pColorTable->SetValueRange(0, 2000);
	//		pColorTable->SetSaturationRange(1, 1);
	pColorTable->SetHueRange(0.667, 0.0);//0.667
	pColorTable->SetTableRange(1000, 2000);
//	pColorTable->SetRampToSQRT();
	pColorTable->SetAboveRangeColor(1, 0, 0, 1);
	pColorTable->UseAboveRangeColorOn();
	//	pColorTable->SetBelowRangeColor(0, 1, 0, 1);
	//	pColorTable->UseBelowRangeColorOn();

	pColorTable->Build();

	vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	vtkSmartPointer<vtkStringArray> array = vtkSmartPointer<vtkStringArray>::New();
//	array->InsertNextValue("E:\\SE33\\Z1.dcm");
//	array->InsertNextValue("E:/testbmp.bmp");//
// 	array->InsertNextValue("E:/testpic2.bmp");//
	array->InsertNextValue("E:/p1.bmp");//
	array->InsertNextValue("E:/p2.bmp");//
	reader->SetFileNames(array);//E:\SE33
	reader->SetFileName("E:\\SE2\\IM1.dcm");
 	reader->Update();

// 	vtkSmartPointer<vtkBMPReader> reader2 = vtkSmartPointer<vtkBMPReader>::New();
// 	reader2->SetFileNames(array);
// 	reader2->Update();

	vtkSmartPointer<vtkScalarBarActor> scalarBar =
		vtkSmartPointer<vtkScalarBarActor>::New();
	scalarBar->SetTitle("vectors");
	scalarBar->SetNumberOfLabels(15);
	scalarBar->SetTextPad(10);
	scalarBar->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
	scalarBar->SetLookupTable(pColorTable);

	vtkSmartPointer<vtkImageViewer2> view = vtkSmartPointer<vtkImageViewer2>::New();
//	view->SetInputConnection(reader->GetOutputPort());

	view->GetRenderer()->AddActor2D(scalarBar);
	vtkSmartPointer<vtkRenderWindowInteractor> ren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	view->SetupInteractor(ren);
	view->Render();
	ren->Start();
	return 0;

}
*/

// class vtkSubclassPlaybackRepresentation : public vtkPlaybackRepresentation
// {
// public:
// 	static vtkSubclassPlaybackRepresentation *New() { return new vtkSubclassPlaybackRepresentation; }
// 	void Play() override { std::cout << "play\n"; }
// 	void Stop() override { std::cout << "stop\n"; }
// 	void ForwardOneFrame() override { std::cout << "forward one frame\n"; }
// 	void BackwardOneFrame() override { std::cout << "backward one frame\n"; }
// 	void JumpToBeginning() override { std::cout << "jump to beginning\n"; }
// 	void JumpToEnd() override { std::cout << "jump to end\n"; }
// };

#include "vtkImageActor.h"
/*
int main()
{
	vtkDICOMImageReader *dcmReader = vtkDICOMImageReader::New();
//	dcmReader->SetDirectoryName("E:\\dataofdcm\\mydata\\onetime");
	dcmReader->SetFileName("E:\\dataofdcm\\mydata\\onetime\\Z1.dcm");
//	dcmReader->SetDataByteOrderToLittleEndian();
	double x, y, z;
// 	dcmReader->GetDataSpacing(x, y, z);
// 	dcmReader->SetDataSpacing(x, y, z);
// 	vtkImageShiftScale *shifter = vtkImageShiftScale::New();
// 	shifter->SetInputConnection(dcmReader->GetOutputPort());
// 	shifter->SetShift(70);
// 	shifter->SetScale(0.5);
// 	shifter->SetOutputScalarTypeToUnsignedChar();

	vtkImageViewer2* view2 = vtkImageViewer2::New();
	view2->SetInputConnection(dcmReader->GetOutputPort());


	vtkRenderWindowInteractor*iRen = vtkRenderWindowInteractor::New();//设置绘制窗口的交互
	view2->SetupInteractor(iRen);
	view2->Render();
	iRen->Start();
}
*/

#include "vtkInteractorEventRecorder.h"
/*
int main()
{
	vtkSmartPointer<vtkRenderer> ren1 =
		vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renWin =
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren1);

	vtkSmartPointer<vtkRenderWindowInteractor> iren =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	// Create a test pipeline
	//
	vtkSmartPointer<vtkSphereSource> ss =
		vtkSmartPointer<vtkSphereSource>::New();
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(ss->GetOutputPort());
	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	// Create the widget
	vtkSmartPointer<vtkPlaybackRepresentation> rep =
		vtkSmartPointer<vtkPlaybackRepresentation>::New();

	vtkSmartPointer<vtkPlaybackWidget> widget =
		vtkSmartPointer<vtkPlaybackWidget>::New();
	widget->SetInteractor(iren);
	widget->SetRepresentation(rep);

	// Add the actors to the renderer, set the background and size
	//
	ren1->AddActor(actor);
	ren1->SetBackground(0.1, 0.2, 0.4);
	renWin->SetSize(300, 300);

	// record events
	vtkSmartPointer<vtkInteractorEventRecorder> recorder =
		vtkSmartPointer<vtkInteractorEventRecorder>::New();
	recorder->SetInteractor(iren);
	recorder->SetFileName("c:/record.log");
	//  recorder->Record();
	//  recorder->ReadFromInputStringOn();
	//  recorder->SetInputString(eventLog);

	// render the image
	//
	iren->Initialize();
	renWin->Render();
	widget->On();
	//  recorder->Play();

	// Remove the observers so we can go interactive. Without this the "-I"
	// testing option fails.
	recorder->Off();

	iren->Start();

	return EXIT_SUCCESS;
}
*/

/*************************     三角网格      ********************************/
#include <vtkSmartPointer.h>  
#include <vtkPolyDataReader.h>  
#include <vtkPolyData.h>  
#include <vtkSurfaceReconstructionFilter.h>  
#include <vtkContourFilter.h>  
#include <vtkVertexGlyphFilter.h>  
#include <vtkPolyDataMapper.h>  
#include <vtkActor.h>  
#include <vtkRenderer.h>  
#include <vtkCamera.h>  
#include <vtkRenderWindow.h>  
#include <vtkRenderWindowInteractor.h>  
#include <vtkProperty.h>  
/*
int main()
{
vtkSmartPointer<vtkPolyDataReader> reader =
vtkSmartPointer<vtkPolyDataReader>::New();
reader->SetFileName("E:\\fran_cut.vtk");
reader->Update();

vtkSmartPointer<vtkPolyData> points =
vtkSmartPointer<vtkPolyData>::New();
points->SetPoints(reader->GetOutput()->GetPoints()); //获得网格模型中的几何数据：点集

vtkSmartPointer<vtkSurfaceReconstructionFilter> surf =
vtkSmartPointer<vtkSurfaceReconstructionFilter>::New();
surf->SetInputData(points);
surf->SetNeighborhoodSize(20);
surf->SetSampleSpacing(0.005);//0.005
surf->Update();

vtkSmartPointer<vtkContourFilter> contour =
vtkSmartPointer<vtkContourFilter>::New();
contour->SetInputConnection(surf->GetOutputPort());
contour->SetValue(0, 0.0);
contour->Update();
//////////////////////////////////////////////////
vtkSmartPointer <vtkVertexGlyphFilter> vertexGlyphFilter =
vtkSmartPointer<vtkVertexGlyphFilter>::New();
vertexGlyphFilter->AddInputData(points);
vertexGlyphFilter->Update();
vtkSmartPointer<vtkPolyDataMapper> pointMapper =
vtkSmartPointer<vtkPolyDataMapper>::New();
pointMapper->SetInputData(vertexGlyphFilter->GetOutput());
pointMapper->ScalarVisibilityOff();

vtkSmartPointer<vtkActor> pointActor =
vtkSmartPointer<vtkActor>::New();
pointActor->SetMapper(pointMapper);
pointActor->GetProperty()->SetColor(1, 0, 0);
pointMapper->ScalarVisibilityOff();
pointActor->GetProperty()->SetPointSize(4);
pointActor->GetProperty()->SetRepresentationToWireframe();//设定网格显示方式

vtkSmartPointer<vtkPolyDataMapper> contourMapper =
vtkSmartPointer<vtkPolyDataMapper>::New();
contourMapper->SetInputData(contour->GetOutput());
vtkSmartPointer<vtkActor> contourActor =
vtkSmartPointer<vtkActor>::New();
contourActor->SetMapper(contourMapper);
///////////////
double pointView[4] = { 0, 0, 0.5, 1 };
double contourView[4] = { 0.5, 0, 1, 1 };

vtkSmartPointer<vtkRenderer> pointRender =
vtkSmartPointer<vtkRenderer>::New();
pointRender->AddActor(pointActor);
pointRender->SetViewport(pointView);
pointRender->SetBackground(1, 1, 1);

vtkSmartPointer<vtkRenderer> contourRender =
vtkSmartPointer<vtkRenderer>::New();
contourRender->AddActor(contourActor);
contourRender->SetViewport(contourView);
contourRender->SetBackground(0, 1, 0);

pointRender->GetActiveCamera()->SetPosition(0, -1, 0);
pointRender->GetActiveCamera()->SetFocalPoint(0, 0, 0);
pointRender->GetActiveCamera()->SetViewUp(0, 0, 1);
pointRender->GetActiveCamera()->Azimuth(30);
pointRender->GetActiveCamera()->Elevation(30);
pointRender->ResetCamera();
contourRender->SetActiveCamera(pointRender->GetActiveCamera());

vtkSmartPointer<vtkRenderWindow> rw =
vtkSmartPointer<vtkRenderWindow>::New();
rw->AddRenderer(pointRender);
rw->AddRenderer(contourRender);
rw->SetSize(640, 320);
rw->SetWindowName("3D Surface Reconstruction ");
rw->Render();

vtkSmartPointer<vtkRenderWindowInteractor> rwi =
vtkSmartPointer<vtkRenderWindowInteractor>::New();
rwi->SetRenderWindow(rw);
rwi->Initialize();
rwi->Start();

return 0;
}
*/

#include "vtkTriangleMeshPointNormals.h"
#include "vtkDelaunay3D.h"
#include "vtkShrinkFilter.h"
/*
int main()
{

vtkSmartPointer<vtkPoints> m_Points = vtkSmartPointer<vtkPoints>::New();
vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();   //_存放细胞顶点，用于渲染（显示点云所必须的）
vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
vtkDelaunay3D* dela = vtkDelaunay3D::New();
vtkShrinkFilter* shrink = vtkShrinkFilter::New();

// 	//_读进点云数据信息
// 	FILE *fp;
// 	fp = fopen("E:\\data4.dat", "r"); //2DpointDatas.txt
// 	if (!fp)
// 	{
// 		printf("打开文件失败！！\n");
// 		int m;
// 		cin >> m;
// 		exit(0);
// 	}
// 	double x = 0, y = 0, z = 0;
// 	int i = 0;
// 	while (!feof(fp))
// 	{
// 		fscanf(fp, "%lf %lf %lf", &x, &y, &z);
// 		m_Points->InsertPoint(i, z, x, y);      //_加入点信息
// 		vertices->InsertNextCell(1);     //_加入细胞顶点信息----用于渲染点集
// 		vertices->InsertCellPoint(i);
// 		i++;
// 	}
// 	fclose(fp);

//_创建待显示数据源

vtkSmartPointer<vtkPoints> m_Points23 = vtkSmartPointer<vtkPoints>::New();

m_Points23->InsertNextPoint(0, 0, 0);
m_Points23->InsertNextPoint(0, 1, 0);
m_Points23->InsertNextPoint(1, 0, 1);
m_Points23->InsertNextPoint(1, 1, 1);
m_Points23->InsertNextPoint(2, 0, 0);
m_Points23->InsertNextPoint(2, 1, 0);
m_Points23->InsertNextPoint(3, 0, 1);
m_Points23->InsertNextPoint(3, 1, 1);

vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();   //_存放细胞顶点，用于渲染（显示点云所必须的）


cells->InsertNextCell(3);
cells->InsertCellPoint(0);
cells->InsertCellPoint(1);
cells->InsertCellPoint(5);

int sad[3] = { 4, 2, 6 };

static vtkIdType pts[6][4] = { { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 0, 1, 5, 4 },
{ 1, 2, 6, 5 }, { 2, 3, 7, 6 }, { 3, 0, 4, 7 } };

for (size_t i = 0; i < 6; i++)
{
cells->InsertNextCell(4, pts[i]);
}


// 		cells->InsertCellPoint(0);
// 		cells->InsertCellPoint(1);
// 		cells->InsertCellPoint(5);


polyData->SetPoints(m_Points23);       //_设置点集
//	polyData->SetVerts(cells);        //_设置渲染顶点
polyData->SetPolys(cells);        //_设置渲染顶点
vtkTriangleFilter* triangle = vtkTriangleFilter::New();
triangle->SetInputData(polyData);
triangle->Update();

vtkContourFilter* contour = vtkContourFilter::New();
contour->SetInputData(polyData);
contour->Update();

vtkCylinderSource* cylinder = vtkCylinderSource::New();
cylinder->SetHeight(2.0);

cylinder->SetRadius(1.0);

cylinder->SetResolution(10);


vtkPolyDataMapper* mapper22 = vtkPolyDataMapper::New();
//	mapper22->SetInputConnection(triangle->GetOutputPort());
mapper22->SetInputData(polyData);
mapper22->Update();

vtkPolyDataWriter *writer = vtkPolyDataWriter::New();
writer->SetFileName("E:\\poly.vtk");
writer->SetInputData(polyData);
writer->Write();
system("pause");

vtkRenderer *ren = vtkRenderer::New();
vtkRenderer *ren2 = vtkRenderer::New();

vtkPolyDataReader *reader = vtkPolyDataReader::New();
reader->SetFileName("E:\\fran_cut.vtk");      //*读取网格数据文件
vtkDecimatePro *deci = vtkDecimatePro::New();    //进行精简
deci->SetInputConnection(reader->GetOutputPort());
//	deci->SetInputData(polyData);
deci->SetTargetReduction(0.9);
deci->PreserveTopologyOn();

//设置优化
vtkSmoothPolyDataFilter *smoother = vtkSmoothPolyDataFilter::New();

//	smoother->SetInputData(polyData);
smoother->SetInputConnection(deci->GetOutputPort());
smoother->SetNumberOfIterations(50);
vtkPolyDataNormals *normals = vtkPolyDataNormals::New();
normals->SetInputConnection(smoother->GetOutputPort());
normals->FlipNormalsOn();

vtkTriangleMeshPointNormals* highnormals = vtkTriangleMeshPointNormals::New();
highnormals->SetInputConnection(smoother->GetOutputPort());


vtkPolyDataMapper *map1 = vtkPolyDataMapper::New();
map1->SetInputConnection(dela->GetOutputPort());

vtkPolyDataMapper *map2 = vtkPolyDataMapper::New();
map2->SetInputConnection(normals->GetOutputPort());

vtkActor *actor1 = vtkActor::New();
actor1->SetMapper(mapper22);
//	actor1->GetProperty()->SetColor(0.38, 0.7, 0.12);  //设定曲面背面颜色
map1->ScalarVisibilityOff();
//	actor1->GetProperty()->SetRepresentationToWireframe();//设定网格显示方式

vtkActor *actor2 = vtkActor::New();
actor2->SetMapper(map2);
actor2->GetProperty()->SetColor(1.0000, 0, 0);  //设定曲面背面颜色
map2->ScalarVisibilityOff();
actor2->GetProperty()->SetRepresentationToWireframe();//*设定网格显示方式

vtkProperty *back_prop = vtkProperty::New();     //新建属性，设定曲面前面颜色
back_prop->SetDiffuseColor(1, 1, 0);
actor1->SetBackfaceProperty(back_prop);

ren->AddActor(actor1);
ren2->AddActor(actor2);

ren->SetBackground(0.1, 0.8, 0.8);          //设定背景色
ren2->SetBackground(0.6, 0.8, 0.8);          //设定背景色

vtkRenderWindow* win = vtkRenderWindow::New();
win->AddRenderer(ren);
win->AddRenderer(ren2);
win->SetSize(1200, 600);
ren->SetViewport(0, 0, 0.5, 1);
ren2->SetViewport(0.5, 0, 1, 1);

//建立交互窗口，设定交互方式
vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
iren->SetRenderWindow(win);
vtkInteractorStyleTrackballCamera *style =
vtkInteractorStyleTrackballCamera::New();
iren->SetInteractorStyle(style);

iren->Start();

ren->Delete();
win->Delete();
iren->Delete();

return 0;
}
*/

#include "vtkDelaunay2D.h"

// int main()
// {
// 	vtkSmartPointer<vtkPoints> m_Points = vtkSmartPointer<vtkPoints>::New();
// 	vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();   //_存放细胞顶点，用于渲染（显示点云所必须的）  
// 	vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
// 	vtkSmartPointer<vtkPolyDataMapper> pointMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
// 	vtkSmartPointer<vtkActor> pointActor = vtkSmartPointer<vtkActor>::New();
// 	vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer< vtkRenderer>::New();
// 	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
// 	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
// 	vtkSmartPointer<vtkInteractorStyleTrackballCamera> istyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
// 
// 	//_读进点云数据信息  
// 	FILE *fp = NULL; 
// 	fp = fopen("E:\\data4.dat", "r"); //2DpointDatas.txt  
// 	if (!fp)
// 	{
// 		printf("打开文件失败！！\n");
// 		int m;
// 		cin >> m;
// 		exit(0);
// 	}
// 	double x = 0, y = 0, z = 0;
// 	int i = 0;
// 	while (!feof(fp))
// 	{ 
// 		fscanf(fp, "%lf %lf %lf", &x, &y, &z);
// 		m_Points->InsertPoint(i, x, y, z);      //_加入点信息  
// 		vertices->InsertNextCell(1);     //_加入细胞顶点信息----用于渲染点集  
// 		vertices->InsertCellPoint(i);
// 
// 		i++;
// 	}
// 	fclose(fp);
// 
// 	//_创建待显示数据源  
// 
// 	polyData->SetPoints(m_Points);       //_设置点集  
// 	polyData->SetVerts(vertices);        //_设置渲染顶点  
// 
// 
// 	vtkDelaunay2D* dela2d = vtkDelaunay2D::New();
// 	dela2d->SetInputData(polyData);
// 	dela2d->SetSourceData(polyData);
// 
// 	pointMapper->SetInputData(polyData);
// 
// 	pointActor->SetMapper(pointMapper);
// 
// 	pointActor->GetProperty()->SetColor(1.0000, 0, 0);  //设定曲面背面颜色
// 	pointActor->GetProperty()->SetAmbient(0.5);
// 	pointActor->GetProperty()->SetPointSize(2);
// 	pointActor->GetProperty()->SetRepresentationToWireframe();  
// 	pointActor->GetProperty()->SetRepresentationToSurface();  
// 
// 	ren1->AddActor(pointActor);
// 	ren1->SetBackground(0.6, 0.8, 0.8);          //设定背景色
// 
// 	renWin->AddRenderer(ren1);
// 	renWin->SetSize(800, 800);
// 
// 	iren->SetInteractorStyle(istyle);
// 	iren->SetRenderWindow(renWin);  //交互  
// 
// 	renWin->Render();
// 	iren->Start();
// }

/*
int main()
{
	typedef unsigned int PixelType;
	const unsigned int Dimension = 3;
	typedef itk::Image<PixelType, Dimension> ImageType;
	typedef itk::ImageSeriesReader<ImageType> ReaderType;
	typedef itk::GDCMImageIO ImageIOType;
	typedef itk::ImageToVTKImageFilter<ImageType> trans;
	ReaderType::Pointer reader;

	ImageIOType::Pointer dicomIO;

	ImageType::Pointer image;

	ImageType::SizeType size;
	ImageType::IndexType index = { { 1, 1, 1 } };
	ImageType::PixelType value[3];

	INT16* pixel[3];
	string t_1fileName;

	typedef itk::GDCMSeriesFileNames
		InputNamesGeneratorType;

	InputNamesGeneratorType::Pointer inputNames = InputNamesGeneratorType::New();

	const ReaderType::FileNamesContainer & filenames =
		inputNames->GetInputFileNames();

	vector<std::string> qq;


	for (size_t i = 0; i < 267; i++)
	{
		string fname = "E:\\Release\\LHYSE9\\IM";
		fname = fname + to_string(i);
		qq.push_back(fname);
	}

	reader->SetFileNames(qq);


	//itk
	reader = ReaderType::New();
	dicomIO = ImageIOType::New();
	reader->SetImageIO(dicomIO);
	try
	{
		reader->Update();
	}
	catch (itk::ExceptionObject &err)
	{
		std::cerr << "Read Error" << std::endl;
		std::cerr << err << std::endl;
		return EXIT_FAILURE;
	}


	typedef itk::ImageToVTKImageFilter<ImageType> FilterType;
	FilterType::Pointer connect = FilterType::New();
	connect->SetInput(reader->GetOutput());



	vtkSmartPointer<vtkImageShrink3D> m_shrink = vtkSmartPointer<vtkImageShrink3D>::New();//二次抽样

	m_shrink->SetShrinkFactors(0, 0, 0);//调节绘制图像的精细程度
	m_shrink->AveragingOn();
	m_shrink->SetInputData(connect->GetOutput());
	m_shrink->Update();


	// vtkSmartPointer<vtkImageDataGeometryFilter> geometry = vtkSmartPointer<vtkImageDataGeometryFilter>::New();
	// 
	// geometry->SetInputConnection(m_shrink->GetOutputPort());//结构点提取几何图形
	// geometry->Update();

	vtkSmartPointer<vtkContourFilter> m_skinExtractor = vtkSmartPointer<vtkContourFilter>::New();//生成等值面/线

	m_skinExtractor->SetInputConnection(m_shrink->GetOutputPort());
	m_skinExtractor->SetValue(0, 400);//调整阈值，400以上是骨组织

	vtkSmartPointer<vtkDecimatePro> m_deci = vtkSmartPointer<vtkDecimatePro>::New();//减少网格中三角形的数量

	m_deci->SetTargetReduction(0.3);//减少到70%
	m_deci->SetInputConnection(m_skinExtractor->GetOutputPort());
	m_deci->Update();
	vtkSmartPointer<vtkSmoothPolyDataFilter> m_smooth = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();//拉普拉斯平滑

	m_smooth->SetInputConnection(m_deci->GetOutputPort());
	m_smooth->SetNumberOfIterations(500);
	m_smooth->Update();
	vtkSmartPointer<vtkPolyDataNormals> m_skinNormals = vtkSmartPointer<vtkPolyDataNormals>::New();//计算多边形网格的法线

	m_skinNormals->SetInputConnection(m_smooth->GetOutputPort());
	m_skinNormals->SetComputeCellNormals(1);
	m_skinNormals->SetComputePointNormals(1);
	m_skinNormals->SetFeatureAngle(60.0);//设置定义的锐角
	m_skinNormals->Update();

	vtkSmartPointer<vtkStripper> m_stripper = vtkSmartPointer<vtkStripper>::New();//创造三角形条

	m_stripper->SetInputConnection(m_skinNormals->GetOutputPort());
	m_stripper->Update();

	vtkSmartPointer<vtkTriangleFilter> m_triangle = vtkSmartPointer<vtkTriangleFilter>::New();//将多边形变成三角形条，消耗更少的内存
	m_triangle->SetInputConnection(m_stripper->GetOutputPort());
	m_triangle->Update();

	vtkPolyDataConnectivityFilter* ConnectivityFilter = vtkPolyDataConnectivityFilter::New();
	ConnectivityFilter->SetInputConnection(m_triangle->GetOutputPort());
	ConnectivityFilter->SetExtractionModeToLargestRegion();
	//ConnectivityFilter->Update();

	int qqqqqq = ConnectivityFilter->GetNumberOfExtractedRegions();


	//cout << qqqqqq << endl;

	//定义颜色映射表
	vtkLookupTable *pColorTable = vtkLookupTable::New();
	// 	pColorTable->SetNumberOfColors(6);
	// 	pColorTable->SetTableValue(0, 0, 0, 0, 1.0);
	//  	pColorTable->SetTableValue(-900, 0.0, 1.0, 1.0, 1.0);
	//  	pColorTable->SetTableValue(900, 0.5, 1.0, 0.2, 0.7);
	// 	pColorTable->SetTableValue(900, 1.0, 0.0, 1.0, 1.0);
	// 	pColorTable->SetTableValue(1800, 0.0, 0.0, 1.0, 1.0);
	// 	pColorTable->SetTableValue(5, 1.0, 1.0, 0.0, 1.0);
	//	pColorTable->SetValueRange(0, 1);
	//	pColorTable->SetSaturationRange(1, 1);
	//	pColorTable->SetHueRange(0.4, 0.9);
	pColorTable->SetHueRange(0.667, 0);
	//pColorTable->SetAlphaRange(0.2, 0.8);

	pColorTable->Build();

	vtkSmartPointer<vtkProperty> polyProperty =
		vtkSmartPointer<vtkProperty>::New();
	//volumeProperty->SetInterpolationTypeToLinear();
	//volumeProperty->ShadeOn();  //打开或者关闭阴影测试
	polyProperty->SetAmbient(0.4);		//环境光，数值大，阴影效果不明显
	polyProperty->SetDiffuse(0.6);  //散射光，数值大，显示效果粗糙
	polyProperty->SetSpecular(0.2); //反射光，数值大，显示效果光滑
	//设置不透明度


	vtkSmartPointer<vtkPolyDataMapper> originMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	originMapper->SetInputConnection(m_triangle->GetOutputPort());
	//originMapper->SetInputData(cube);
	//originMapper->ScalarVisibilityOff();
	// originMapper->SetScalarRange(0,800);
	// originMapper->SetLookupTable(pColorTable);


	vtkSmartPointer<vtkActor> originActor =
		vtkSmartPointer<vtkActor>::New();
	originActor->SetMapper(originMapper);
	//originActor->GetProperty()->SetOpacity(0.3);
	originActor->GetProperty()->SetColor(1, 0, 0);
	originActor->SetProperty(polyProperty);


	vtkSmartPointer<vtkRenderer> glyphRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	glyphRenderer->AddActor(originActor);
	glyphRenderer->SetBackground(1, 1, 1);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();

	renderWindow->AddRenderer(glyphRenderer);
	renderWindow->SetSize(1280, 960);
	renderWindow->Render();
	renderWindow->SetWindowName("PolyDataNormal");

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	vtkPlaybackRepresentation* Representation = vtkPlaybackRepresentation::New();


	vtkPlaybackWidget* PlaybackWidget = vtkPlaybackWidget::New();
	PlaybackWidget->SetInteractor(renderWindowInteractor);
	PlaybackWidget->SetRepresentation(Representation);


	renderWindowInteractor->Initialize();
	PlaybackWidget->On();
	renderWindow->Render();
	renderWindowInteractor->Start();


	return 0;
}
*/

class aaa
{
public:

	const char& operator[](size_t position) const
	{
		return pText[position];
	}
	aaa(char* pprr)
	{
		pText = pprr;
	}

	char& operator[](size_t position)
	{
		return
			const_cast<char&>
			(static_cast<const aaa&>(*this)[position]);
	}

private:
	char* pText;

};

class A
{
public:
	A();
	virtual	~A();
	virtual void foo()
	{
		cout << "rua" << endl;
	}
private:

};

A::A()
{
}

A::~A()
{
}
class B :public A
{
public:
	virtual void foo()
	{
		cout << "hello" << endl;
	}
};

class month
{
public:
	month();
	~month();
	static month jan()
	{
		return month(1);
	}


private:
	explicit month(int m);

};

month::month()
{
}

month::~month()
{
}

class cxstr
{
public:
	cxstr();
	~cxstr();
	explicit cxstr(int qq)
	{
		cout << "rua" << endl;
	}
	cxstr(string qq)
	{
		cout << "rua" << endl;
	}

private:

};

cxstr::cxstr()
{
}

cxstr::~cxstr()
{
}


// int main()
// {
// 	char str[] = "hello";
// //	cout << str << " " << *(str+1) << endl;//hello e
// 	const char strr[] = "world";
// 	const aaa ccbb("hello");
// 	
// 	B* bclss = new B;
// 	bclss->foo();
// 	A* aclass = new A;
// 	aclass->foo();
// 
// 	const int ica = 10;
// 	int *ia = const_cast<int*>(&ica);
// 
// 	A* keeper();
// 	A* aakk = keeper();
// 	delete aakk;
// 
// 
// 
// 	return 0;
// }

/*
int main()
{
//
// 	string csPathName = "E:\\ddddddd00000.dat";
// 	WIN32_FIND_DATA fileInfo;
// 	HANDLE hFind;
// 	DWORD fileSize;
// 	hFind = FindFirstFile(csPathName.c_str(), &fileInfo);
// 	if (hFind != INVALID_HANDLE_VALUE)		fileSize = fileInfo.nFileSizeLow;	//得到数据文件大小。
// 	FindClose(hFind);
// 	FILE * file;
// 	ofstream fout;
// 	if ((file = fopen(csPathName.c_str(), "rt")) == NULL)
// 		return false;
// 	char	filedata[500];
// 	int		idata, jdata;
// 	fseek(file, 2, SEEK_SET);
// 	fscanf(file, "%s", filedata);
// 	fscanf(file, "%s", filedata);
//
// 	fscanf(file, "%s", filedata);

string qq,q2;
int ni = 0;
for (ni = 0; ni < 25;ni++)
{
	q2 = "E:\\dataofdcm\\Snake\\Img_sag" + to_string(22 + ni)+"_ins4.dcm";
qq = "E:\\dataofdcm\\Snake\\onetime\\Z" + to_string(ni+1) + ".dcm";//onetime
CopyFile(q2.c_str(), qq.c_str(), TRUE);
cout << "end" << endl;
}

system("pause");

std::ofstream fout("E:\\a123.dat", std::ios::binary);
for (int i = 0; i < 1000;i++)
{
fout.write((char*)&i, sizeof(int));
}

fout.close();

ifstream ffoo("E:\\a123.dat", std::ios::binary);

int ch;

for (int bj = 0; bj < 1000;bj++)
{
ffoo.read((char*)(&ch), sizeof(ch));
if (ch == 100)
{
cout << "rua" << endl;
}
cout << ch << endl;
}

ffoo.close();


}
*/

typedef struct  myaaa
{
	string str;
	//string file2;
	int nb;

} my22;

bool a_less_b(const my22& r, const my22& s)
{
	return r.nb < s.nb;
}


/*****************************************dcm文件分类***********************************************/

#include "itkImageFileWriter.h"
#include "itkMetaDataObject.h"
/*
int main()
{
char t_fileName[128];
my22 mydd1;
vector<my22>myrua;
vector<int> samenum;
int countnum = 0;
//	OutputDebugString(L"start");
for (int i = 0; i < 1; i++) //几个图像就循环几次
{
//	sprintf(t_fileName, "E:\\my projects\\vtktest1\\A\\Z%d.dcm", i);
	sprintf(t_fileName, "E:\\dataofdcm\\mydata\\d0\\Z%d.dcm", i);
//		sprintf_s(t_fileName, "E:\\fen\\SE0\\IM%d", i);
//sprintf_s(t_fileName, "E:\\dataofdcm\\ins4\\Phase1_sag22_ins4.dcm");
//Anatomy
//	reader->SetFileName("E:\\my projects\\vtktest1\\A\\Z1110.dcm");

// 		reader->SetDataByteOrderToLittleEndian();
//
// 	    reader->Update();

typedef unsigned short PixelType;
const unsigned int Dimension = 3;
typedef itk::Image<PixelType, Dimension> ImageType;
typedef itk::ImageSeriesReader<ImageType> ReaderType;
ReaderType::Pointer reader1 = ReaderType::New();

typedef itk::GDCMImageIO ImageIOType;

typedef itk::ImageFileWriter<ImageType> WriterType;
WriterType::Pointer writer = WriterType::New();


//	typedef itk::GDCMSeriesFileNames NamesGeneratorType;
//	NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
//	nameGenerator->SetInputDirectory("E:\\my projects\\vtktest1\\BB");//读取目录

// 		//存储文件名字
// 		typedef std::vector<std::string> FileNamesContainer;
// 		FileNamesContainer fileNames = nameGenerator->GetInputFileNames();
//
// 		int num = fileNames.size();
// 		std::cout << num << std::endl;
//
// 		reader1->SetFileNames(fileNames);
//		reader->SetInput(reader1->GetOutput());

reader1->SetFileName(t_fileName);

ImageIOType::Pointer dicomIO = ImageIOType::New();
reader1->SetImageIO(dicomIO);
reader1->Update();


try
{
reader1->Update();
}
catch (itk::ExceptionObject &err)
{
std::cerr << "Read Error" << std::endl;
std::cerr << err << std::endl;
return EXIT_FAILURE;
}



//create MetaDataDictionary
typedef itk::MetaDataDictionary DictionaryType;
const DictionaryType &dictionary = dicomIO->GetMetaDataDictionary();//const

//dicomIO->GetMetaDataDictionary();

typedef itk::MetaDataObject<std::string> MetaDataStringType;
DictionaryType::ConstIterator itr = dictionary.Begin();
DictionaryType::ConstIterator end = dictionary.End();

mydd1.str = t_fileName;

//myinfo.filename = t_fileName;
//
string rstr;


string str11("0020|0013");
string str22("1");

itk::EncapsulateMetaData<std::string>(const_cast<DictionaryType&>(dictionary), str11, str22);//const转非const
system("pause");

while (itr != end)
{
itk::MetaDataObjectBase::Pointer entry = itr->second;
MetaDataStringType::Pointer entryvalue =
dynamic_cast<MetaDataStringType *>(entry.GetPointer());

if (entryvalue)
{

std::string tagkey = itr->first;
std::string tagvalue = entryvalue->GetMetaDataObjectValue();

std::cout << tagkey << ":" << tagvalue << std::endl;
//	/*0002|0002字段可以标识SOP Class UID，如果是CT就是
//	 1.2.840.10008.5.1.4.1.1.2,如果是MRI就是1.2.840.10008.5.1.4.1.1.4
bool bqq = false;

if (tagkey == "0020|0013")
{
//rstr = tagvalue;
//	cout << tagvalue << endl;
//entryvalue->SetMetaDataObjectValue("1");

}
// 				if (tagkey == "0020|0032")
// 				{
// 					//cout << tagvalue <<endl;
// 					//	myinfo.picpos = tagvalue;
// 					//	myinfo.nb = atoi(tagvalue.c_str());
// 					string my_cstr = tagvalue;
// 					my_cstr = "&&" + my_cstr;
// 					my_cstr += "&&";
//
// 					if (tagvalue == "-36.9982\\-183.521\\148.914 ")
// 					{
// 						//cout << rstr << endl;
// 						//	samenum.push_back(stoi(rstr));
// 						mydd1.nb = stoi(rstr);
//
// 						myrua.push_back(mydd1);
// 					}
//
// 				}

}
++itr;
}


string my_cstr;
dicomIO->GetValueFromTag("0020|9241", my_cstr);
if (my_cstr == "40")
{
countnum++;
dicomIO->GetValueFromTag("0020|0013", my_cstr);
mydd1.nb = atoi(my_cstr.c_str());
myrua.push_back(mydd1);

}

cout << i << ":" << my_cstr << endl;

}
cout  << "   " << countnum << endl;
system("pause");

//	OutputDebugString(L"end");
//排序
sort(myrua.begin(), myrua.end(), a_less_b);
int ni = 0;
for (auto item : myrua)
{
cout << item.nb << item.str << endl;

string qq = "E:\\fen\\SE02\\sd" + to_string(ni);//onetime
CopyFile(item.str.c_str(), qq.c_str(), TRUE);
ni++;

}

//第二种for循环
// 		for (auto item = samenum.cbegin(); item != samenum.cend();item++)
// 		{
// 			cout << *item << endl;
// 		}



return 0;
}
*/


typedef struct  Mydata
{
	int str;
	std::string filename;
	std::string picpos;
	int nb;

} MydataInfo;

 inline bool a_less_b2(const MydataInfo& r, const MydataInfo& s)
{
	return r.str < s.str;
}
 /*
int main()
{
	int randonnum = 0;
	char t_fileName[128];
	MydataInfo myinfo;
	std::vector<MydataInfo> p_md, nshow;
	vector<string> strname;
	vector<int> m_tritime;

	vector<string> strmypicpos;

	for (int i = 1; i < 2101; i++) //几个图像就循环几次  
	{
		sprintf(t_fileName, "E:\\dataofdcm\\mydata\\d0\\Z%d.dcm", i);

		//	reader->SetFileName("E:\\my projects\\vtktest1\\A\\Z1110.dcm");

		// 		reader->SetDataByteOrderToLittleEndian();
		// 
		// 	    reader->Update();

		typedef unsigned short PixelType;
		const unsigned int Dimension = 3;
		typedef itk::Image<PixelType, Dimension> ImageType;
		typedef itk::ImageSeriesReader<ImageType> ReaderType;
		ReaderType::Pointer reader1 = ReaderType::New();

		typedef itk::GDCMImageIO ImageIOType;


		//	typedef itk::GDCMSeriesFileNames NamesGeneratorType;
		//	NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
		//	nameGenerator->SetInputDirectory("E:\\my projects\\vtktest1\\BB");//读取目录

		// 		//存储文件名字 
		// 		typedef std::vector<std::string> FileNamesContainer;
		// 		FileNamesContainer fileNames = nameGenerator->GetInputFileNames();
		// 
		// 		int num = fileNames.size();
		// 		std::cout << num << std::endl;
		// 
		// 		reader1->SetFileNames(fileNames);
		//		reader->SetInput(reader1->GetOutput());

		reader1->SetFileName(t_fileName);

		ImageIOType::Pointer dicomIO = ImageIOType::New();
		reader1->SetImageIO(dicomIO);

		try
		{
			reader1->Update();
		}
		catch (itk::ExceptionObject &err)
		{
			std::cerr << "Read Error" << std::endl;
			std::cerr << err << std::endl;
			return EXIT_FAILURE;
		}

		//create MetaDataDictionary 
		typedef itk::MetaDataDictionary DictionaryType;
		const DictionaryType &dictionary = dicomIO->GetMetaDataDictionary();

		//dicomIO->GetMetaDataDictionary();

		typedef itk::MetaDataObject<std::string> MetaDataStringType;
		DictionaryType::ConstIterator itr = dictionary.Begin();
		DictionaryType::ConstIterator end = dictionary.End();


		myinfo.filename = t_fileName;
		

		while (itr != end)
		{
			itk::MetaDataObjectBase::Pointer entry = itr->second;
			MetaDataStringType::Pointer entryvalue =
				dynamic_cast<MetaDataStringType *>(entry.GetPointer());

			if (entryvalue)
			{
				//string ffnm = filename;
				std::string tagkey = itr->first;
				std::string tagvalue = entryvalue->GetMetaDataObjectValue();
				//	std::cout << tagkey <<":" <<tagvalue<<std::endl;
				//	/*0002|0002字段可以标识SOP Class UID，如果是CT就是
				//	 1.2.840.10008.5.1.4.1.1.2,如果是MRI就是1.2.840.10008.5.1.4.1.1.4



				if (tagkey == "0018|1060")
				{
					//cout << tagvalue <<endl;
					myinfo.nb = atoi(tagvalue.c_str());
					//	myinfo.nb = atoi(tagvalue.c_str());
					if (find(m_tritime.begin(), m_tritime.end(), atoi(tagvalue.c_str())) == m_tritime.end())
					{
						m_tritime.push_back(atoi(tagvalue.c_str()));// atoi(tagvalue)
					}

				}

				if (tagkey == "0020|0013")
				{
					//cout << tagvalue <<endl;
					myinfo.str = atoi(tagvalue.c_str());

				}

				if (tagkey == "0020|0032")
				{
					//cout << tagvalue <<endl;
					myinfo.picpos = tagvalue;
					//	myinfo.nb = atoi(tagvalue.c_str());
					string my_cstr = tagvalue.c_str();
					my_cstr = "&&" + my_cstr;
					my_cstr += "&&";
					//MessageBox(p_MainDlg->GetSafeHwnd(), qq12, "rua", MB_OK);


// 					if (find(strname.begin(), strname.end(), tagvalue) == strname.end())
// 					{
// 						strname.push_back(tagvalue);
// 					}



					if (tagvalue == "-36.9982\\-183.521\\148.914 ")
					{
						++randonnum;
					}

				}

			}
			++itr;
			//	entry->Delete();
			//	entryvalue->Delete();
		}
		p_md.push_back(myinfo);
		//		reader1->Delete();
		//		dicomIO->Delete();

	}
// 	CString qq12;
// 	qq12.Format("%d", randonnum);
// 	MessageBox(p_MainDlg->GetSafeHwnd(), qq12, "rua", MB_OK);

//bifflash = false;
sort(p_md.begin(), p_md.end(), a_less_b2);



sort(m_tritime.begin(), m_tritime.end());

int qq = m_tritime.size();
cout << "************************" << endl;
cout << qq << endl;

for (auto item : m_tritime)
{
	cout << item << endl;
}

//system("pause");

for (size_t i = 0; i < m_tritime.size(); i++)//
{
	string sd2;// = "md E:\\fen\\" + to_string(i + 1);
	string sd = "E:\\fen\\" + to_string(i+1);
	sd2 = "md " + sd;
	system(sd2.c_str());
	int ni = 0;
for (auto item : p_md)
{

//	cout << item.nb << item.str << endl;
	if (item.nb == m_tritime[i])
	{

		string qq;
		qq= sd + "\\Z" + to_string(ni) + ".dcm";//onetime
	CopyFile(item.filename.c_str(), qq.c_str(), TRUE);
	ni++;
	}
}
}

//cout << ni << endl;
cout << "end" << endl;
//	ni++;


}
*/






/*
int main()
{
	vtkSmartPointer<vtkPolyDataReader> reader =
		vtkSmartPointer<vtkPolyDataReader>::New();
	reader->SetFileName("E:\\fran_cut.vtk");
	reader->Update();

	vtkSmartPointer<vtkPolyData> points =
		vtkSmartPointer<vtkPolyData>::New();
	points->SetPoints(reader->GetOutput()->GetPoints()); //获得网格模型中的几何数据：点集  

	vtkSmartPointer<vtkSurfaceReconstructionFilter> surf =
		vtkSmartPointer<vtkSurfaceReconstructionFilter>::New();
	surf->SetInputData(points);
	surf->SetNeighborhoodSize(20);
	surf->SetSampleSpacing(0.005);
	surf->Update();

	vtkSmartPointer<vtkContourFilter> contour =
		vtkSmartPointer<vtkContourFilter>::New();
	contour->SetInputConnection(surf->GetOutputPort());
	contour->SetValue(0, 0.0);
	contour->Update();
	//////////////////////////////////////////////////  
	vtkSmartPointer <vtkVertexGlyphFilter> vertexGlyphFilter =
		vtkSmartPointer<vtkVertexGlyphFilter>::New();
	vertexGlyphFilter->AddInputData(points);
	vertexGlyphFilter->Update();
	vtkSmartPointer<vtkPolyDataMapper> pointMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	pointMapper->SetInputData(vertexGlyphFilter->GetOutput());
	pointMapper->ScalarVisibilityOff();

	vtkSmartPointer<vtkActor> pointActor =
		vtkSmartPointer<vtkActor>::New();
	pointActor->SetMapper(pointMapper);
	pointActor->GetProperty()->SetColor(1, 0, 0);
	pointActor->GetProperty()->SetPointSize(4);

	vtkSmartPointer<vtkPolyDataMapper> contourMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper->SetInputData(contour->GetOutput());
	vtkSmartPointer<vtkActor> contourActor =
		vtkSmartPointer<vtkActor>::New();
	contourActor->SetMapper(contourMapper);
	///////////////  
	double pointView[4] = { 0, 0, 0.5, 1 };
	double contourView[4] = { 0.5, 0, 1, 1 };

	vtkSmartPointer<vtkRenderer> pointRender =
		vtkSmartPointer<vtkRenderer>::New();
	pointRender->AddActor(pointActor);
	pointRender->SetViewport(pointView);
	pointRender->SetBackground(1, 1, 1);

	vtkSmartPointer<vtkRenderer> contourRender =
		vtkSmartPointer<vtkRenderer>::New();
	contourRender->AddActor(contourActor);
	contourRender->SetViewport(contourView);
	contourRender->SetBackground(0, 1, 0);

	pointRender->GetActiveCamera()->SetPosition(0, -1, 0);
	pointRender->GetActiveCamera()->SetFocalPoint(0, 0, 0);
	pointRender->GetActiveCamera()->SetViewUp(0, 0, 1);
	pointRender->GetActiveCamera()->Azimuth(30);
	pointRender->GetActiveCamera()->Elevation(30);
	pointRender->ResetCamera();
	contourRender->SetActiveCamera(pointRender->GetActiveCamera());

	vtkSmartPointer<vtkRenderWindow> rw =
		vtkSmartPointer<vtkRenderWindow>::New();
	rw->AddRenderer(pointRender);
	rw->AddRenderer(contourRender);
	rw->SetSize(640, 320);
	rw->SetWindowName("3D Surface Reconstruction ");
	rw->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> rwi =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	rwi->SetRenderWindow(rw);
	rwi->Initialize();
	rwi->Start();

	return 0;
}
*/


/*****************************dos新建文件夹***********************************/
/*

int main()
{
	system("md E:\\lalalalal");
	return 0;
}
*/

struct tecplotdata
{
	int x;
	int y;
	int z;
	float u;
	float v;
	float w;
	float speed;
};

vector<tecplotdata> mydata11;


void returnvalue()
{

	tecplotdata data;
	data.x = 132;
	data.y = 15;
	data.z = 12; data.u = 1;
	data.v = 156;
	data.w = 167;
	data.speed = 123;
	mydata11.push_back(data);

	//return data;

}
/*
int main()
{
int n1 = 0;
float d2 = 0;

char str3[500];
tecplotdata mydata = {0};

returnvalue();

for (auto item : mydata11)
{
cout << item.x << item.y << endl;
}

//	 mydata =  mydata11.front();

cout << mydata.x << endl;


FILE *fp;
fp = fopen("E:\\ttss.txt", "r+");
if (fp ==NULL)
{
cout << "error" << endl;
return 0;
}
// 	while (!feof(fp))
// 	{
// 	//	fscanf(fp, "%d\n%f\n%s", &n1, &d2, str3);
// 	//	printf("%d %f %s\n", n1, d2, str3);
// 	//	cout << n1 << " " << d2 << " " << str3 << endl;
// 	}
fscanf(fp, "%s", str3);
cout << str3 << endl;
fscanf(fp, "%s", str3);
cout << str3 << endl;
fscanf(fp, "%s", str3);
cout << str3 << endl;


fclose(fp);
cout << "end" << endl;
return 0;

}
*/

/*
int main()
{
	string csPathName = "E:\\testdat\\Data1.dat";

	WIN32_FIND_DATA fileInfo;
	HANDLE hFind;
	DWORD fileSize;
	hFind = FindFirstFile(csPathName.c_str(), &fileInfo);
	if (hFind != INVALID_HANDLE_VALUE)		fileSize = fileInfo.nFileSizeLow;	//得到数据文件大小。
	FindClose(hFind);
	FILE * file;
	if ((file = fopen(csPathName.c_str(), "rt")) == NULL)		return false;			//
	char	filedata[500];
	int		idata, jdata;
	fscanf(file, "%s", filedata);											//（获得首个字符串）
	if (strcmp(filedata, "TITLE"))		return false;						//if not tecplot file.，比较字符串


	//打开PTV结果。。。。。。
	DWORD lopnumber, lopstart;
	int mi, mj, mk;
	while (strcmp(filedata, "DOUBLE)"))
	{
		fscanf(file, "%s", filedata);
	}
	int x = 0, y = 0, z = 0;
	double  u = 0, v = 0, w = 0;

	for (size_t i = 0; i < 256*256*84; i++)
	{
		fscanf(file, "%d\t%d\t%d\t%f\t%f\t%f", &x, &y, &z, &u, &v, &w);

//		fscanf(file, "%d", xx);
	}

}

*/


//读取tecplot模板
/*
int main()
{
string csPathName = "E:\\testdat\\Data1.dat";

WIN32_FIND_DATA fileInfo;
HANDLE hFind;
DWORD fileSize;
hFind = FindFirstFile(csPathName.c_str(), &fileInfo);
if (hFind != INVALID_HANDLE_VALUE)		fileSize = fileInfo.nFileSizeLow;	//得到数据文件大小。
FindClose(hFind);
FILE * file;
if ((file = fopen(csPathName.c_str(), "rt")) == NULL)		return false;			//
char	filedata[500];
int		idata, jdata;
fscanf(file, "%s", filedata);											//（获得首个字符串）
if (strcmp(filedata, "TITLE"))		return false;						//if not tecplot file.，比较字符串
int lopnumber = 0;
int		bDataType = 0;	//0--unknow; 2--2 dimension; 3--3 dimension.
fscanf(file, "%s", filedata);

fscanf(file, "%s", filedata);
int nnn;
if (nnn =1)
{
if (nnn =1)
//	{ AfxMessageBox("Not formal MicroVec PIV V3.5.1 data format !", MB_OK); return false; }
int A;

{		//打开PTV结果。。。。。。
DWORD lopnumber, lopstart;
int mi, mj, mk;
while (strcmp(filedata, "DOUBLE)"))
{
fscanf(file, "%s", filedata);
}
fseek(file, 2, SEEK_SET);
fscanf(file, "%s", filedata);

if (fileSize > 5000)	lopstart = fileSize - 5000;	else	lopstart = 1;
fseek(file, lopstart, SEEK_SET);
for (lopnumber = lopstart; lopnumber <= fileSize; lopnumber++)
{
fscanf(file, "%s", filedata);
if (!strcmp(filedata, "[VectorFileSetting]") || !strcmp(filedata, "向量文件设置:"))
{
float	ftemp;
fscanf(file, "%s", filedata); fscanf(file, "%s", filedata);
fscanf(file, "%f", &ftemp);	fscanf(file, "%f", &ftemp);
fscanf(file, "%f", &ftemp);		fscanf(file, "%f", &ftemp);
fscanf(file, "%f", &ftemp);		fscanf(file, "%f", &ftemp);
fscanf(file, "%f", &ftemp);		fscanf(file, "%f", &ftemp);
fscanf(file, "%f", &ftemp);	fscanf(file, "%f", &ftemp);
fscanf(file, "%f", &ftemp);		fscanf(file, "%f", &ftemp);

break;
}
}
if (lopnumber >= fileSize)
//			{ AfxMessageBox("No formal MicroVec PIV V3.5.1 data found !", MB_OK); return false; }
fseek(file, 1L, SEEK_SET);
lopnumber = 0;
while (strcmp(filedata, "I="))	{ lopnumber++;	if (lopnumber > 200)	return false;	fscanf(file, "%s", filedata); }
fscanf(file, " %d ,", &idata);	fscanf(file, "%s", filedata);		fscanf(file, "%d", &jdata);
jdata = 1;
int	nDouble = 0;
while (strcmp(filedata, "DT=(DOUBLE"))	{ fscanf(file, "%s", filedata);	nDouble++;	if (nDouble > 1000)	break; }
nDouble = 1;
while (strcmp(filedata, "DOUBLE)"))		{ fscanf(file, "%s", filedata);	nDouble++;	if (nDouble > 1000)	break; }
if (!(nDouble == 12))
//	AfxMessageBox("Not MicroVec PIV V3.5.1 data file format !", MB_OK);
//	m_dVectorList[m_nImagePointer].m_nMode = 1;
int	filelen = idata*jdata;
//	m_nBufferVector = m_nImagePointer;
//	m_dVectorList[m_nImagePointer].m_pivJobInfo.imagewd = m_ImageResolution.cx;
//	m_dVectorList[m_nImagePointer].m_pivJobInfo.imageht = m_ImageResolution.cy;
//	m_dVectorList[m_nImagePointer].m_nVector = m_dVectorList[m_nImagePointer].m_pivJobInfo.mapwd = idata;

//	PIVVECTOR * m_hVectorBack = new	PIVVECTOR[m_dVectorList[m_nImagePointer].m_nVector];
//	delete	m_dVectorList[m_nImagePointer].m_pVector;
//	m_dVectorList[m_nImagePointer].m_bVector = false;
//	m_dVectorList[m_nImagePointer].m_pVector = new	PIVVECTOR[m_dVectorList[m_nImagePointer].m_nVector];
//	if (m_dVectorList[m_nImagePointer].m_pVector == NULL)
//	{ CString		sTitle = "  RAM operate Error, Please retry !";	SetTitle(sTitle);	Sleep(500); }
//	CString	stemp;
double	Vecmax, Vecmin, VZsum;
Vecmax = -10000000.0;	Vecmin = 10000000.0;
VZsum = 0;
float	fx0, fy0, fz0, fxd, fyd, fzd, fvel, fdia, fadu, fadv, fadw, fadvel;
}
}

}
*/

// bool PIVOpenVectorFile(CString csPathName, DWORD m_nImagePointer, bool m_bVectorColor)
// {
// 	WIN32_FIND_DATA fileInfo;
// 	HANDLE hFind;
// 	DWORD fileSize;
// 	hFind = FindFirstFile(csPathName, &fileInfo);
// 	if (hFind != INVALID_HANDLE_VALUE)		fileSize = fileInfo.nFileSizeLow;	//得到数据文件大小。
// 	FindClose(hFind);
// 	FILE * file;
// 	if ((file = fopen(csPathName, "rt")) == NULL)		return false;			//
// 	char	filedata[500];
// 	int		idata, jdata;
// 	fscanf(file, "%s", filedata);											//（获得首个字符串）
// 	if (strcmp(filedata, "TITLE"))		return false;						//if not tecplot file.，比较字符串
// 	int lopnumber = 0;
// 	int		bDataType = 0;	//0--unknow; 2--2 dimension; 3--3 dimension.
// 	fscanf(file, "%s", filedata);		fscanf(file, "%s", filedata);
// 	if (strcmp(filedata, "\"PIV"))
// 	{
// 		if (strcmp(filedata, "\"PTV"))	{ AfxMessageBox("Not formal MicroVec PIV V3.5.1 data format !", MB_OK); return false; }
// 		else
// 		{		//打开PTV结果。。。。。。
// 			DWORD lopnumber, lopstart;
// 			if (fileSize > 5000)	lopstart = fileSize - 5000;	else	lopstart = 1;
// 			fseek(file, lopstart, SEEK_SET);
// 			for (lopnumber = lopstart; lopnumber <= fileSize; lopnumber++)
// 			{
// 				fscanf(file, "%s", filedata);
// 				if (!strcmp(filedata, "[VectorFileSetting]") || !strcmp(filedata, "向量文件设置:"))
// 				{
// 					float	ftemp;
// 					fscanf(file, "%s", filedata); fscanf(file, "%s", filedata);
// 					fscanf(file, "%f", &ftemp);	m_dOutputVector.m_fXA = ftemp;	fscanf(file, "%f", &ftemp);	m_dOutputVector.m_fXB = ftemp;
// 					fscanf(file, "%f", &ftemp);	m_dOutputVector.m_fYA = ftemp;	fscanf(file, "%f", &ftemp);	m_dOutputVector.m_fYB = ftemp;
// 					fscanf(file, "%f", &ftemp);	m_dOutputVector.m_fZA = ftemp;	fscanf(file, "%f", &ftemp);	m_dOutputVector.m_fZB = ftemp;
// 					fscanf(file, "%f", &ftemp);	m_dOutputVector.m_fUA = ftemp;	fscanf(file, "%f", &ftemp);	m_dOutputVector.m_fUB = ftemp;
// 					fscanf(file, "%f", &ftemp);	m_dOutputVector.m_fVA = ftemp;	fscanf(file, "%f", &ftemp);	m_dOutputVector.m_fVB = ftemp;
// 					fscanf(file, "%f", &ftemp);	m_dOutputVector.m_fWA = ftemp;	fscanf(file, "%f", &ftemp);	m_dOutputVector.m_fWB = ftemp;
// 					m_pRulerDlg->m_fResult = m_dOutputVector.m_fXA;				m_pRulerDlg->m_fVResult = m_dOutputVector.m_fUA;
// 					break;
// 				}
// 			}
// 			if (lopnumber >= fileSize)	{ AfxMessageBox("No formal MicroVec PIV V3.5.1 data found !", MB_OK); return false; }
// 			fseek(file, 1L, SEEK_SET);
// 			lopnumber = 0;
// 			while (strcmp(filedata, "I="))	{ lopnumber++;	if (lopnumber > 200)	return false;	fscanf(file, "%s", filedata); }
// 			fscanf(file, " %d ,", &idata);	fscanf(file, "%s", filedata);		fscanf(file, "%d", &jdata);
// 			jdata = 1;
// 			int	nDouble = 0;
// 			while (strcmp(filedata, "DT=(DOUBLE"))	{ fscanf(file, "%s", filedata);	nDouble++;	if (nDouble > 1000)	break; }
// 			nDouble = 1;
// 			while (strcmp(filedata, "DOUBLE)"))		{ fscanf(file, "%s", filedata);	nDouble++;	if (nDouble > 1000)	break; }
// 			if (!(nDouble == 12))	AfxMessageBox("Not MicroVec PIV V3.5.1 data file format !", MB_OK);
// 			m_dVectorList[m_nImagePointer].m_nMode = 1;
// 			int	filelen = idata*jdata;
// 			m_nBufferVector = m_nImagePointer;
// 			m_dVectorList[m_nImagePointer].m_pivJobInfo.imagewd = m_ImageResolution.cx;
// 			m_dVectorList[m_nImagePointer].m_pivJobInfo.imageht = m_ImageResolution.cy;
// 			m_dVectorList[m_nImagePointer].m_nVector = m_dVectorList[m_nImagePointer].m_pivJobInfo.mapwd = idata;
// 
// 			PIVVECTOR * m_hVectorBack = new	PIVVECTOR[m_dVectorList[m_nImagePointer].m_nVector];
// 			delete	m_dVectorList[m_nImagePointer].m_pVector;
// 			m_dVectorList[m_nImagePointer].m_bVector = false;
// 			m_dVectorList[m_nImagePointer].m_pVector = new	PIVVECTOR[m_dVectorList[m_nImagePointer].m_nVector];
// 			if (m_dVectorList[m_nImagePointer].m_pVector == NULL)	{ CString		sTitle = "  RAM operate Error, Please retry !";	SetTitle(sTitle);	Sleep(500); }
// 			CString	stemp;
// 			double	Vecmax, Vecmin, VZsum;
// 			Vecmax = -10000000.0;	Vecmin = 10000000.0;
// 			VZsum = 0;
// 			float	fx0, fy0, fz0, fxd, fyd, fzd, fvel, fdia, fadu, fadv, fadw, fadvel;
// 			if (m_dOutputVector.m_bTecplot)
// 			{
// 				for (int lop = 0; lop < filelen; lop++)
// 				{
// 					fscanf(file, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t", &fx0, &fy0, &fz0, &fxd, &fyd, &fzd, &fvel, &fdia, &fadu, &fadv, &fadw, &fadvel);
// 					(m_hVectorBack + lop)->x0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->x0 = (fx0 - m_dOutputVector.m_fXB) / m_dOutputVector.m_fXA;
// 					(m_hVectorBack + lop)->y0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->y0 = m_ImageResolution.cy - (fy0 - m_dOutputVector.m_fYB) / m_dOutputVector.m_fYA;
// 					(m_hVectorBack + lop)->z0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->z0 = (fz0 - m_dOutputVector.m_fZB) / m_dOutputVector.m_fZA;
// 					(m_hVectorBack + lop)->fxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd = (double)(fxd - m_dOutputVector.m_fUB) / m_dOutputVector.m_fUA;
// 					(m_hVectorBack + lop)->xd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->xd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd;
// 					(m_hVectorBack + lop)->fyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd = -(double)(fyd - m_dOutputVector.m_fVB) / m_dOutputVector.m_fVA;
// 					(m_hVectorBack + lop)->yd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->yd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd;
// 					(m_hVectorBack + lop)->fzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd = (double)(fzd - m_dOutputVector.m_fWB) / m_dOutputVector.m_fWA;
// 					(m_hVectorBack + lop)->zd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->zd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd;
// 					(m_hVectorBack + lop)->fvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel = (fvel);
// 					(m_hVectorBack + lop)->fradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fradial = (fdia) / m_dOutputVector.m_fXA;;
// 					(m_hVectorBack + lop)->stdfxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfxd = 0;
// 					(m_hVectorBack + lop)->stdfyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfyd = 0;
// 					(m_hVectorBack + lop)->stdfzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfzd = 0;
// 					(m_hVectorBack + lop)->stdfvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvel = 0;
// 					(m_hVectorBack + lop)->stdfvor = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvor = 0;
// 					(m_hVectorBack + lop)->std_fxy = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxy = 0;
// 					(m_hVectorBack + lop)->std_fyz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fyz = 0;
// 					(m_hVectorBack + lop)->std_fxz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxz = 0;
// 					(m_hVectorBack + lop)->std_fxxyyzz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxxyyzz = 0;
// 					(m_hVectorBack + lop)->ftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->ftangent = 0;
// 					(m_hVectorBack + lop)->stdfradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfradial = 0;
// 					(m_hVectorBack + lop)->stdftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdftangent = 0;
// 
// 					if ((m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel > Vecmax)	Vecmax = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel;
// 					if ((m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel < Vecmin)	Vecmin = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel;
// 					VZsum += (m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd;
// 					(m_dVectorList[m_nImagePointer].m_pVector + lop)->flag = 1;
// 				}
// 			}
// 			else
// 			{
// 				for (int lop = 0; lop < filelen; lop++)
// 				{
// 					fscanf(file, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t", &fx0, &fy0, &fz0, &fxd, &fyd, &fzd, &fvel, &fdia, &fadu, &fadv, &fadw, &fadvel);
// 					(m_hVectorBack + lop)->x0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->x0 = (fx0 - m_dOutputVector.m_fXB) / m_dOutputVector.m_fXA;
// 					(m_hVectorBack + lop)->y0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->y0 = (fy0 - m_dOutputVector.m_fYB) / m_dOutputVector.m_fYA;
// 					(m_hVectorBack + lop)->z0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->z0 = (fz0 - m_dOutputVector.m_fZB) / m_dOutputVector.m_fZA;
// 					(m_hVectorBack + lop)->fxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd = (double)(fxd - m_dOutputVector.m_fUB) / m_dOutputVector.m_fUA;
// 					(m_hVectorBack + lop)->xd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->xd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd;
// 					(m_hVectorBack + lop)->fyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd = -(double)(fyd - m_dOutputVector.m_fVB) / m_dOutputVector.m_fVA;
// 					(m_hVectorBack + lop)->yd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->yd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd;
// 					(m_hVectorBack + lop)->fzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd = (double)(fzd - m_dOutputVector.m_fWB) / m_dOutputVector.m_fWA;
// 					(m_hVectorBack + lop)->zd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->zd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd;
// 					(m_hVectorBack + lop)->fvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel = (fvel);
// 					(m_hVectorBack + lop)->fradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fradial = (fdia) / m_dOutputVector.m_fXA;;
// 					(m_hVectorBack + lop)->stdfxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfxd = 0;
// 					(m_hVectorBack + lop)->stdfyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfyd = 0;
// 					(m_hVectorBack + lop)->stdfzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfzd = 0;
// 					(m_hVectorBack + lop)->stdfvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvel = 0;
// 					(m_hVectorBack + lop)->stdfvor = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvor = 0;
// 					(m_hVectorBack + lop)->std_fxy = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxy = 0;
// 					(m_hVectorBack + lop)->std_fyz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fyz = 0;
// 					(m_hVectorBack + lop)->std_fxz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxz = 0;
// 					(m_hVectorBack + lop)->std_fxxyyzz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxxyyzz = 0;
// 					(m_hVectorBack + lop)->ftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->ftangent = 0;
// 					(m_hVectorBack + lop)->stdfradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfradial = 0;
// 					(m_hVectorBack + lop)->stdftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdftangent = 0;
// 
// 					if ((m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel > Vecmax)	Vecmax = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel;
// 					if ((m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel < Vecmin)	Vecmin = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel;
// 					VZsum += (m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd;
// 					(m_dVectorList[m_nImagePointer].m_pVector + lop)->flag = 1;
// 				}
// 			}
// 
// 			if (m_bVectorColor)
// 			{
// 				double	vecscal = Vecmax - Vecmin;
// 				int	nColor;
// 				double	nBias;
// 				for (DWORD i = 0; i<m_dVectorList[m_nImagePointer].m_nVector; i++)
// 				{	//设定向量颜色
// 					if ((m_dVectorList[m_nImagePointer].m_pVector + i)->flag == 0)
// 						(m_dVectorList[m_nImagePointer].m_pVector + i)->m_cVecColor = RGB(0, 0, 0);
// 					else
// 					{
// 						nBias = ((m_dVectorList[m_nImagePointer].m_pVector + i)->fvel - Vecmin);
// 						if (nBias>(vecscal*3.0 / 4.0))
// 						{
// 							nColor = (int)((nBias - vecscal * 3 / 4) * 4 * 255.0 / vecscal);	(m_dVectorList[m_nImagePointer].m_pVector + i)->m_cVecColor = RGB(255, (255 - nColor), 0);
// 						}
// 						else if (nBias > (vecscal*2.0 / 4.0))
// 						{
// 							nColor = (int)((nBias - vecscal * 2 / 4) * 4 * 255.0 / vecscal);	(m_dVectorList[m_nImagePointer].m_pVector + i)->m_cVecColor = RGB(nColor, 255, 0);
// 						}
// 						else if (nBias > (vecscal / 4.0))
// 						{
// 							nColor = (int)((nBias - vecscal / 4)*4.0*255.0 / vecscal);	(m_dVectorList[m_nImagePointer].m_pVector + i)->m_cVecColor = RGB(0, 255, (255 - nColor));
// 						}
// 						else
// 						{
// 							nColor = (int)((nBias)*4.0*255.0 / vecscal);			(m_dVectorList[m_nImagePointer].m_pVector + i)->m_cVecColor = RGB(0, nColor, 255);
// 						}
// 					}
// 				}
// 			}
// 			lopnumber = 0;
// 			CString sfiledata;
// 			while (strcmp(filedata, "ImageFileName-A:") && strcmp(filedata, "互相关计算图像源文件A:"))
// 			{
// 				lopnumber++;	if (lopnumber > 200)	return false;		fscanf(file, "%s", filedata);
// 			}
// 			fscanf(file, "%s", filedata);			sFileName[m_nImagePointer] = filedata;
// 			lopnumber = 0;
// 			while (strcmp(filedata, "ImageFileName-B:") && strcmp(filedata, "互相关计算图像源文件B:"))		{ lopnumber++;		if (lopnumber > 200)	return false;	fscanf(file, "%s", filedata); }
// 			fscanf(file, "%s", filedata);
// 			if ((m_nImagePointer + m_nTwoImage) > m_nImageBuffer)  sFileName[m_nImageBuffer] = filedata;
// 			else sFileName[m_nImagePointer + m_nTwoImage] = filedata;
// 			lopnumber = 0;
// 			while (strcmp(filedata, "ParticleSizeLowerLimit:") && strcmp(filedata, "粒子尺寸下限:"))		{ lopnumber++;		if (lopnumber > 200)	return false;		fscanf(file, "%s", filedata); }
// 			fscanf(file, "%s", filedata);
// 			sfiledata = filedata;		sfiledata.Delete(0, 2);
// 			sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 			m_dMV_PTV_Setting.m_nMinX = atoi(sfiledata);
// 			fscanf(file, "%s", filedata);
// 			sfiledata = filedata;		sfiledata.Delete(0, 2);
// 			m_dMV_PTV_Setting.m_nMinY = atoi(sfiledata);
// 			lopnumber = 0;
// 			while (strcmp(filedata, "ParticleSizeUpperLimit:") && strcmp(filedata, "粒子尺寸上限:"))		{ lopnumber++;		if (lopnumber > 200)	return false;		fscanf(file, "%s", filedata); }
// 			fscanf(file, "%s", filedata);
// 			sfiledata = filedata;		sfiledata.Delete(0, 2);
// 			sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 			m_dMV_PTV_Setting.m_nMaxX = atoi(sfiledata);
// 			fscanf(file, "%s", filedata);
// 			sfiledata = filedata;		sfiledata.Delete(0, 2);
// 			m_dMV_PTV_Setting.m_nMaxY = atoi(sfiledata);
// 			lopnumber = 0;
// 			while (strcmp(filedata, "StraddleInterval:") && strcmp(filedata, "两幅图像间隔:"))		{ lopnumber++;		if (lopnumber > 200)	return false;		fscanf(file, "%s", filedata); }
// 			fscanf(file, "%s", filedata);		m_nTwoImage = atoi(filedata);
// 			if (m_nTwoImage<0)	m_nTwoImage = 1;
// 			lopnumber = 0;
// 			while (strcmp(filedata, "BackgroundGate:") && strcmp(filedata, "背景阈值:"))			{ lopnumber++;		if (lopnumber>200)	return false;		fscanf(file, "%s", filedata); }
// 			fscanf(file, "%s", filedata);
// 			m_dMV_PTV_Setting.m_nGate = atoi(filedata);
// 			lopnumber = 0;
// 			while (strcmp(filedata, "PartileNumber:") && strcmp(filedata, "搜索个数:"))			{ lopnumber++;		if (lopnumber > 200)	return false;		fscanf(file, "%s", filedata); }
// 			fscanf(file, "%s", filedata);
// 			m_dMV_PTV_Setting.m_nNumber = atoi(filedata);
// 			lopnumber = 0;
// 			while (strcmp(filedata, "VectorLengthLimit:") && strcmp(filedata, "向量长度限制:"))		{ lopnumber++;		if (lopnumber > 200)	return false;		fscanf(file, "%s", filedata); }
// 			fscanf(file, "%s", filedata);
// 			m_dMV_PTV_Setting.m_nLimit = atoi(filedata);
// 			lopnumber = 0;
// 			while (strcmp(filedata, "SearchBlackParticle:") && strcmp(filedata, "搜索黑色粒子:"))		{ lopnumber++;		if (lopnumber > 200)	return false;		fscanf(file, "%s", filedata); }
// 			fscanf(file, "%s", filedata);
// 			m_dMV_PTV_Setting.m_bDarkParticle = (boolean)atoi(filedata);
// 			lopnumber = 0;
// 			while (strcmp(filedata, "UsingPIVResult:") && strcmp(filedata, "参考PIV结果:"))		{ lopnumber++;		if (lopnumber > 200)	return false;		fscanf(file, "%s", filedata); }
// 			fscanf(file, "%s", filedata);
// 			m_dMV_PTV_Setting.m_bPIVProcess = (boolean)atoi(filedata);
// 			lopnumber = 1;
// 			while (strcmp(filedata, "[RulerSetting]") && strcmp(filedata, "标尺窗口参数:"))	{ lopnumber++;		if (lopnumber > 200)	break;		fscanf(file, "%s", filedata); }
// 			if (lopnumber<200)
// 			{
// 				lopnumber = 0;
// 				while (strcmp(filedata, "TopLeft:") && strcmp(filedata, "左上:"))	{ lopnumber++;	if (lopnumber>200)	return false;		fscanf(file, "%s", filedata); }
// 				fscanf(file, "%s", filedata);
// 				sfiledata = filedata;
// 				sfiledata.Delete(0, 1);
// 				sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 				m_pRulerDlg->m_fPosTLx = (atof(sfiledata));
// 				fscanf(file, "%s", filedata);
// 				sfiledata = filedata;
// 				sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 				m_pRulerDlg->m_fPosTLy = (atof(sfiledata));
// 				lopnumber = 0;
// 				while (strcmp(filedata, "TopRight:") && strcmp(filedata, "右上:"))	{ lopnumber++;	if (lopnumber > 200)	return false;		fscanf(file, "%s", filedata); }
// 				fscanf(file, "%s", filedata);
// 				sfiledata = filedata;
// 				sfiledata.Delete(0, 1);
// 				sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 				m_pRulerDlg->m_fPosTRx = (atof(sfiledata));
// 				fscanf(file, "%s", filedata);
// 				sfiledata = filedata;
// 				sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 				m_pRulerDlg->m_fPosTRy = (atof(sfiledata));
// 				lopnumber = 0;
// 				while (strcmp(filedata, "LeftBottom:") && strcmp(filedata, "左下:"))	{ lopnumber++;	if (lopnumber > 200)	return false;		fscanf(file, "%s", filedata); }
// 				fscanf(file, "%s", filedata);
// 				sfiledata = filedata;
// 				sfiledata.Delete(0, 1);
// 				sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 				m_pRulerDlg->m_fPosBLx = (atof(sfiledata));
// 				fscanf(file, "%s", filedata);
// 				sfiledata = filedata;
// 				sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 				m_pRulerDlg->m_fPosBLy = (atof(sfiledata));
// 				lopnumber = 0;
// 				while (strcmp(filedata, "RightBottom:") && strcmp(filedata, "右下:"))	{ lopnumber++;	if (lopnumber > 200)	return false;		fscanf(file, "%s", filedata); }
// 				fscanf(file, "%s", filedata);
// 				sfiledata = filedata;
// 				sfiledata.Delete(0, 1);
// 				sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 				m_pRulerDlg->m_fPosBRx = (atof(sfiledata));
// 				fscanf(file, "%s", filedata);
// 				sfiledata = filedata;
// 				sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 				m_pRulerDlg->m_fPosBRy = (atof(sfiledata));
// 				m_pRulerDlg->m_bRulerDlg = true;
// 				if (m_pRulerDlg->GetSafeHwnd() == 0)	m_pRulerDlg->Create();
// 				else	m_pRulerDlg->ShowWindow(SW_SHOW);
// 				m_pRulerDlg->UpdateData(false);
// 			}
// 			else	{ m_pRulerDlg->m_bRulerDlg = false;		m_pRulerDlg->DestroyWindow(); }
// 			fclose(file);
// 			delete m_hVectorBack;
// 		}
// 	}
// 	else		//打开PIV结果。。。。。。。  
// 	{
// 		DWORD lopnumber, lopstart;
// 		if (fileSize > 1500)	lopstart = fileSize - 1500;	else	lopstart = 1;
// 		int rtt = fseek(file, lopstart, SEEK_SET);
// 		for (lopnumber = lopstart; lopnumber <= fileSize; lopnumber++)
// 		{
// 			fscanf(file, "%s", filedata);
// 			if (!strcmp(filedata, "[VectorFileSetting]") || !strcmp(filedata, "向量文件设置:"))
// 			{
// 				float	ftemp;
// 				fscanf(file, "%s", filedata); fscanf(file, "%s", filedata);
// 				fscanf(file, "%f", &ftemp);		m_dOutputVector.m_fXA = ftemp;		fscanf(file, "%f", &ftemp);		m_dOutputVector.m_fXB = ftemp;
// 				fscanf(file, "%f", &ftemp);		m_dOutputVector.m_fYA = ftemp;		fscanf(file, "%f", &ftemp);		m_dOutputVector.m_fYB = ftemp;
// 				fscanf(file, "%f", &ftemp);		m_dOutputVector.m_fZA = ftemp;		fscanf(file, "%f", &ftemp);		m_dOutputVector.m_fZB = ftemp;
// 				fscanf(file, "%f", &ftemp);		m_dOutputVector.m_fUA = ftemp;		fscanf(file, "%f", &ftemp);		m_dOutputVector.m_fUB = ftemp;
// 				fscanf(file, "%f", &ftemp);		m_dOutputVector.m_fVA = ftemp;		fscanf(file, "%f", &ftemp);		m_dOutputVector.m_fVB = ftemp;
// 				fscanf(file, "%f", &ftemp);		m_dOutputVector.m_fWA = ftemp;		fscanf(file, "%f", &ftemp);		m_dOutputVector.m_fWB = ftemp;
// 				m_pRulerDlg->m_fResult = m_dOutputVector.m_fXA;				m_pRulerDlg->m_fVResult = m_dOutputVector.m_fUA;
// 				break;
// 			}
// 		}
// 		if (lopnumber >= fileSize)	{ AfxMessageBox("No valid PIV data setting found !", MB_OK); return false; }
// 		fseek(file, 1L, SEEK_SET);
// 		lopnumber = 0;
// 		while (strcmp(filedata, "I="))	{ lopnumber++;	if (lopnumber > 200)	return false;	fscanf(file, "%s", filedata); }
// 		fscanf(file, " %d ,", &idata);	fscanf(file, "%s", filedata);		fscanf(file, "%d", &jdata);
// 		int	nDouble = 0;
// 		while (strcmp(filedata, "DT=(DOUBLE"))	{ fscanf(file, "%s", filedata);		nDouble++;	if (nDouble > 1000)	break; }
// 		nDouble = 1;
// 		while (strcmp(filedata, "DOUBLE)"))		{ fscanf(file, "%s", filedata);		nDouble++;	if (nDouble > 1000)	break; }
// 		if (!((nDouble == 17) || (nDouble == 13) || (nDouble == 8)))	AfxMessageBox("No valid PIV data format !", MB_OK);
// 		if (nDouble == 17)	m_dVectorList[m_nImagePointer].m_nMode = 4;
// 		else		m_dVectorList[m_nImagePointer].m_nMode = 0;
// 		int	filelen = idata*jdata;
// 		m_nBufferVector = m_nImagePointer;
// 		m_dVectorList[m_nImagePointer].m_pivJobInfo.imagewd = m_ImageResolution.cx;
// 		m_dVectorList[m_nImagePointer].m_pivJobInfo.imageht = m_ImageResolution.cy;
// 		m_dVectorList[m_nImagePointer].m_nVector = m_dVectorList[m_nImagePointer].m_pivJobInfo.mapwd = idata;
// 		m_dVectorList[m_nImagePointer].m_pivJobInfo.mapht = jdata;
// 		m_dVectorList[m_nImagePointer].m_nVector = m_dVectorList[m_nImagePointer].m_nVector * m_dVectorList[m_nImagePointer].m_pivJobInfo.mapht;		//vector numbers.
// 		PIVVECTOR * m_hVectorBack = new	PIVVECTOR[m_dVectorList[m_nImagePointer].m_nVector];
// 		delete	m_dVectorList[m_nImagePointer].m_pVector;
// 		m_dVectorList[m_nImagePointer].m_pVector = new	PIVVECTOR[m_dVectorList[m_nImagePointer].m_nVector];
// 		if (m_dVectorList[m_nImagePointer].m_pVector == NULL)	{ CString		sTitle = " RAM operate Error, Please retry !";	SetTitle(sTitle);	Sleep(500); }
// 		m_dVectorList[m_nImagePointer].m_bVector = false;
// 
// 		CString	stemp;
// 		double	Vecmax, Vecmin, VZsum;
// 		Vecmax = -10000000.0;	Vecmin = 10000000.0;
// 		VZsum = 0;
// 		float	fx0, fy0, fz0, fxd, fyd, fzd, fvel, fvor, fstdu, fstdv, fstdw, fstds, fstdvor, fstdxy, fstdyz, fstdxz, fstdxxyyzz;
// 		if (m_dOutputVector.m_bTecplot)
// 		{
// 			for (int lop = 0; lop < filelen; lop++)
// 			{
// 				if (nDouble == 8)
// 				{
// 					fscanf(file, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t", &fx0, &fy0, &fz0, &fxd, &fyd, &fzd, &fvel, &fvor);
// 					(m_hVectorBack + lop)->x0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->x0 = (fx0 - m_dOutputVector.m_fXB) / m_dOutputVector.m_fXA;
// 					(m_hVectorBack + lop)->y0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->y0 = m_ImageResolution.cy - (fy0 - m_dOutputVector.m_fYB) / m_dOutputVector.m_fYA;
// 					(m_hVectorBack + lop)->z0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->z0 = (fz0 - m_dOutputVector.m_fZB) / m_dOutputVector.m_fZA;
// 					(m_hVectorBack + lop)->fxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd = (fxd - m_dOutputVector.m_fUB) / m_dOutputVector.m_fUA;
// 					(m_hVectorBack + lop)->xd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->xd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd;
// 					(m_hVectorBack + lop)->fyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd = -(fyd - m_dOutputVector.m_fVB) / m_dOutputVector.m_fVA;
// 					(m_hVectorBack + lop)->yd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->yd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd;
// 					(m_hVectorBack + lop)->fzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd = (fzd - m_dOutputVector.m_fWB) / m_dOutputVector.m_fWA;
// 					(m_hVectorBack + lop)->zd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->zd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd;
// 					(m_hVectorBack + lop)->fvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel = fvel;
// 					(m_hVectorBack + lop)->fvor = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvor = fvor*m_pRulerDlg->m_fDTime / 1000.0;
// 					(m_hVectorBack + lop)->stdfxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfxd = 0;
// 					(m_hVectorBack + lop)->stdfyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfyd = 0;
// 					(m_hVectorBack + lop)->stdfzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfzd = 0;
// 					(m_hVectorBack + lop)->stdfvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvel = 0;
// 					(m_hVectorBack + lop)->stdfvor = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvor = 0;
// 					(m_hVectorBack + lop)->fradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fradial = 0;
// 					(m_hVectorBack + lop)->ftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->ftangent = 0;
// 					(m_hVectorBack + lop)->stdfradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfradial = 0;
// 					(m_hVectorBack + lop)->stdftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdftangent = 0;
// 				}
// 				else if (nDouble == 13)
// 				{
// 					fscanf(file, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t", &fx0, &fy0, &fz0, &fxd, &fyd, &fzd, &fvel, &fvor, &fstdu, &fstdv, &fstdw, &fstds, &fstdvor);
// 					(m_hVectorBack + lop)->x0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->x0 = (fx0 - m_dOutputVector.m_fXB) / m_dOutputVector.m_fXA;
// 					(m_hVectorBack + lop)->y0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->y0 = m_ImageResolution.cy - (fy0 - m_dOutputVector.m_fYB) / m_dOutputVector.m_fYA;
// 					(m_hVectorBack + lop)->z0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->z0 = (fz0 - m_dOutputVector.m_fZB) / m_dOutputVector.m_fZA;
// 					(m_hVectorBack + lop)->fxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd = (double)(fxd - m_dOutputVector.m_fUB) / m_dOutputVector.m_fUA;
// 					(m_hVectorBack + lop)->xd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->xd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd;
// 					(m_hVectorBack + lop)->fyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd = -(double)(fyd - m_dOutputVector.m_fVB) / m_dOutputVector.m_fVA;
// 					(m_hVectorBack + lop)->yd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->yd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd;
// 					(m_hVectorBack + lop)->fzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd = (double)(fzd - m_dOutputVector.m_fWB) / m_dOutputVector.m_fWA;
// 					(m_hVectorBack + lop)->zd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->zd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd;
// 					(m_hVectorBack + lop)->fvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel = fvel;
// 					(m_hVectorBack + lop)->fvor = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvor = fvor*m_pRulerDlg->m_fDTime / 1000.0;
// 					(m_hVectorBack + lop)->stdfxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfxd = (fstdu - m_dOutputVector.m_fUB) / m_dOutputVector.m_fUA;
// 					(m_hVectorBack + lop)->stdfyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfyd = (fstdv - m_dOutputVector.m_fVB) / m_dOutputVector.m_fVA;
// 					(m_hVectorBack + lop)->stdfzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfzd = (fstdw - m_dOutputVector.m_fWB) / m_dOutputVector.m_fWA;
// 					(m_hVectorBack + lop)->stdfvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvel = fstds;
// 					(m_hVectorBack + lop)->stdfvor = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvor = fstdvor*m_pRulerDlg->m_fDTime / 1000.0;
// 					(m_hVectorBack + lop)->std_fxy = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxy = 0;
// 					(m_hVectorBack + lop)->std_fyz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fyz = 0;
// 					(m_hVectorBack + lop)->std_fxz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxz = 0;
// 					(m_hVectorBack + lop)->std_fxxyyzz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxxyyzz = 0;
// 					(m_hVectorBack + lop)->fradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fradial = 0;
// 					(m_hVectorBack + lop)->ftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->ftangent = 0;
// 					(m_hVectorBack + lop)->stdfradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfradial = 0;
// 					(m_hVectorBack + lop)->stdftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdftangent = 0;
// 				}
// 				else
// 				{
// 					fscanf(file, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t", &fx0, &fy0, &fz0, &fxd, &fyd, &fzd, &fvel, &fvor, &fstdu, &fstdv, &fstdw, &fstds, &fstdvor, &fstdxy, &fstdyz, &fstdxz, &fstdxxyyzz);
// 					(m_hVectorBack + lop)->x0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->x0 = (fx0 - m_dOutputVector.m_fXB) / m_dOutputVector.m_fXA;
// 					(m_hVectorBack + lop)->y0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->y0 = m_ImageResolution.cy - (fy0 - m_dOutputVector.m_fYB) / m_dOutputVector.m_fYA;
// 					(m_hVectorBack + lop)->z0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->z0 = (fz0 - m_dOutputVector.m_fZB) / m_dOutputVector.m_fZA;
// 					(m_hVectorBack + lop)->fxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd = (fxd - m_dOutputVector.m_fUB) / m_dOutputVector.m_fUA;
// 					(m_hVectorBack + lop)->xd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->xd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd;
// 					(m_hVectorBack + lop)->fyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd = -(fyd - m_dOutputVector.m_fVB) / m_dOutputVector.m_fVA;
// 					(m_hVectorBack + lop)->yd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->yd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd;
// 					(m_hVectorBack + lop)->fzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd = (fzd - m_dOutputVector.m_fWB) / m_dOutputVector.m_fWA;
// 					(m_hVectorBack + lop)->zd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->zd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd;
// 					(m_hVectorBack + lop)->fvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel = fvel;
// 					(m_hVectorBack + lop)->fvor = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvor = fvor*m_pRulerDlg->m_fDTime / 1000.0;
// 					(m_hVectorBack + lop)->stdfxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfxd = (fstdu - m_dOutputVector.m_fUB) / m_dOutputVector.m_fUA;
// 					(m_hVectorBack + lop)->stdfyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfyd = (fstdv - m_dOutputVector.m_fVB) / m_dOutputVector.m_fVA;
// 					(m_hVectorBack + lop)->stdfzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfzd = (fstdw - m_dOutputVector.m_fWB) / m_dOutputVector.m_fWA;
// 					(m_hVectorBack + lop)->stdfvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvel = fstds;
// 					(m_hVectorBack + lop)->stdfvor = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvor = fstdvor*m_pRulerDlg->m_fDTime / 1000.0;
// 					(m_hVectorBack + lop)->std_fxy = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxy = fstdxy;
// 					(m_hVectorBack + lop)->std_fyz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fyz = fstdyz;
// 					(m_hVectorBack + lop)->std_fxz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxz = fstdxz;
// 					(m_hVectorBack + lop)->std_fxxyyzz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxxyyzz = fstdxxyyzz;
// 					(m_hVectorBack + lop)->fradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fradial = 0;
// 					(m_hVectorBack + lop)->ftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->ftangent = 0;
// 					(m_hVectorBack + lop)->stdfradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfradial = 0;
// 					(m_hVectorBack + lop)->stdftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdftangent = 0;
// 
// 				}
// 				if ((m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel > Vecmax)	Vecmax = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel;
// 				if ((m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel < Vecmin)	Vecmin = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel;
// 				VZsum += (m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd;
// 				(m_dVectorList[m_nImagePointer].m_pVector + lop)->flag = 1;
// 			}
// 		}
// 		else
// 		{
// 			for (int lop = 0; lop < filelen; lop++)
// 			{
// 				if (nDouble == 8)
// 				{
// 					fscanf(file, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t", &fx0, &fy0, &fz0, &fxd, &fyd, &fzd, &fvel, &fvor);
// 					(m_hVectorBack + lop)->x0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->x0 = (fx0 - m_dOutputVector.m_fXB) / m_dOutputVector.m_fXA;
// 					(m_hVectorBack + lop)->y0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->y0 = (fy0 - m_dOutputVector.m_fYB) / m_dOutputVector.m_fYA;
// 					(m_hVectorBack + lop)->z0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->z0 = (fz0 - m_dOutputVector.m_fZB) / m_dOutputVector.m_fZA;
// 					(m_hVectorBack + lop)->fxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd = (fxd - m_dOutputVector.m_fUB) / m_dOutputVector.m_fUA;
// 					(m_hVectorBack + lop)->xd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->xd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd;
// 					(m_hVectorBack + lop)->fyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd = (fyd - m_dOutputVector.m_fVB) / m_dOutputVector.m_fVA;
// 					(m_hVectorBack + lop)->yd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->yd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd;
// 					(m_hVectorBack + lop)->fzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd = (fzd - m_dOutputVector.m_fWB) / m_dOutputVector.m_fWA;
// 					(m_hVectorBack + lop)->zd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->zd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd;
// 					(m_hVectorBack + lop)->fvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel = fvel;
// 					(m_hVectorBack + lop)->fvor = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvor = fvor*m_pRulerDlg->m_fDTime / 1000.0;
// 					(m_hVectorBack + lop)->stdfxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfxd = 0;
// 					(m_hVectorBack + lop)->stdfyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfyd = 0;
// 					(m_hVectorBack + lop)->stdfzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfzd = 0;
// 					(m_hVectorBack + lop)->stdfvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvel = 0;
// 					(m_hVectorBack + lop)->stdfvor = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvor = 0;
// 					(m_hVectorBack + lop)->fradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fradial = 0;
// 					(m_hVectorBack + lop)->ftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->ftangent = 0;
// 					(m_hVectorBack + lop)->stdfradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfradial = 0;
// 					(m_hVectorBack + lop)->stdftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdftangent = 0;
// 
// 				}
// 				else if (nDouble == 13)
// 				{
// 					fscanf(file, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t", &fx0, &fy0, &fz0, &fxd, &fyd, &fzd, &fvel, &fvor, &fstdu, &fstdv, &fstdw, &fstds, &fstdvor);
// 					(m_hVectorBack + lop)->x0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->x0 = (fx0 - m_dOutputVector.m_fXB) / m_dOutputVector.m_fXA;
// 					(m_hVectorBack + lop)->y0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->y0 = (fy0 - m_dOutputVector.m_fYB) / m_dOutputVector.m_fYA;
// 					(m_hVectorBack + lop)->z0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->z0 = (fz0 - m_dOutputVector.m_fZB) / m_dOutputVector.m_fZA;
// 					(m_hVectorBack + lop)->fxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd = (double)(fxd - m_dOutputVector.m_fUB) / m_dOutputVector.m_fUA;
// 					(m_hVectorBack + lop)->xd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->xd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd;
// 					(m_hVectorBack + lop)->fyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd = (double)(fyd - m_dOutputVector.m_fVB) / m_dOutputVector.m_fVA;
// 					(m_hVectorBack + lop)->yd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->yd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd;
// 					(m_hVectorBack + lop)->fzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd = (double)(fzd - m_dOutputVector.m_fWB) / m_dOutputVector.m_fWA;
// 					(m_hVectorBack + lop)->zd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->zd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd;
// 					(m_hVectorBack + lop)->fvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel = fvel;
// 					(m_hVectorBack + lop)->fvor = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvor = fvor*m_pRulerDlg->m_fDTime / 1000.0;
// 					(m_hVectorBack + lop)->stdfxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfxd = (fstdu - m_dOutputVector.m_fUB) / m_dOutputVector.m_fUA;
// 					(m_hVectorBack + lop)->stdfyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfyd = (fstdv - m_dOutputVector.m_fVB) / m_dOutputVector.m_fVA;
// 					(m_hVectorBack + lop)->stdfzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfzd = (fstdw - m_dOutputVector.m_fWB) / m_dOutputVector.m_fWA;
// 					(m_hVectorBack + lop)->stdfvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvel = fstds;
// 					(m_hVectorBack + lop)->stdfvor = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvor = fstdvor*m_pRulerDlg->m_fDTime / 1000.0;
// 					(m_hVectorBack + lop)->std_fxy = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxy = 0;
// 					(m_hVectorBack + lop)->std_fyz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fyz = 0;
// 					(m_hVectorBack + lop)->std_fxz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxz = 0;
// 					(m_hVectorBack + lop)->std_fxxyyzz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxxyyzz = 0;
// 					(m_hVectorBack + lop)->fradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fradial = 0;
// 					(m_hVectorBack + lop)->ftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->ftangent = 0;
// 					(m_hVectorBack + lop)->stdfradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfradial = 0;
// 					(m_hVectorBack + lop)->stdftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdftangent = 0;
// 				}
// 				else
// 				{
// 					fscanf(file, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t", &fx0, &fy0, &fz0, &fxd, &fyd, &fzd, &fvel, &fvor, &fstdu, &fstdv, &fstdw, &fstds, &fstdvor, &fstdxy, &fstdyz, &fstdxz, &fstdxxyyzz);
// 					(m_hVectorBack + lop)->x0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->x0 = (fx0 - m_dOutputVector.m_fXB) / m_dOutputVector.m_fXA;
// 					(m_hVectorBack + lop)->y0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->y0 = (fy0 - m_dOutputVector.m_fYB) / m_dOutputVector.m_fYA;
// 					(m_hVectorBack + lop)->z0 = (m_dVectorList[m_nImagePointer].m_pVector + lop)->z0 = (fz0 - m_dOutputVector.m_fZB) / m_dOutputVector.m_fZA;
// 					(m_hVectorBack + lop)->fxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd = (fxd - m_dOutputVector.m_fUB) / m_dOutputVector.m_fUA;
// 					(m_hVectorBack + lop)->xd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->xd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fxd;
// 					(m_hVectorBack + lop)->fyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd = (fyd - m_dOutputVector.m_fVB) / m_dOutputVector.m_fVA;
// 					(m_hVectorBack + lop)->yd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->yd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fyd;
// 					(m_hVectorBack + lop)->fzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd = (fzd - m_dOutputVector.m_fWB) / m_dOutputVector.m_fWA;
// 					(m_hVectorBack + lop)->zd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->zd = (int)(m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd;
// 					(m_hVectorBack + lop)->fvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel = fvel;
// 					(m_hVectorBack + lop)->fvor = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvor = fvor*m_pRulerDlg->m_fDTime / 1000.0;
// 					(m_hVectorBack + lop)->stdfxd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfxd = (fstdu - m_dOutputVector.m_fUB) / m_dOutputVector.m_fUA;
// 					(m_hVectorBack + lop)->stdfyd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfyd = (fstdv - m_dOutputVector.m_fVB) / m_dOutputVector.m_fVA;
// 					(m_hVectorBack + lop)->stdfzd = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfzd = (fstdw - m_dOutputVector.m_fWB) / m_dOutputVector.m_fWA;
// 					(m_hVectorBack + lop)->stdfvel = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvel = fstds;
// 					(m_hVectorBack + lop)->stdfvor = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfvor = fstdvor*m_pRulerDlg->m_fDTime / 1000.0;
// 					(m_hVectorBack + lop)->std_fxy = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxy = fstdxy;
// 					(m_hVectorBack + lop)->std_fyz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fyz = fstdyz;
// 					(m_hVectorBack + lop)->std_fxz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxz = fstdxz;
// 					(m_hVectorBack + lop)->std_fxxyyzz = (m_dVectorList[m_nImagePointer].m_pVector + lop)->std_fxxyyzz = fstdxxyyzz;
// 					(m_hVectorBack + lop)->fradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fradial = 0;
// 					(m_hVectorBack + lop)->ftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->ftangent = 0;
// 					(m_hVectorBack + lop)->stdfradial = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdfradial = 0;
// 					(m_hVectorBack + lop)->stdftangent = (m_dVectorList[m_nImagePointer].m_pVector + lop)->stdftangent = 0;
// 
// 				}
// 				if ((m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel > Vecmax)	Vecmax = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel;
// 				if ((m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel < Vecmin)	Vecmin = (m_dVectorList[m_nImagePointer].m_pVector + lop)->fvel;
// 				VZsum += (m_dVectorList[m_nImagePointer].m_pVector + lop)->fzd;
// 				(m_dVectorList[m_nImagePointer].m_pVector + lop)->flag = 1;
// 			}
// 		}
// 
// 		if (VZsum != 0)
// 		{	//ptv/piv计算模式区分。
// 			if (m_dVectorList[m_nImagePointer].m_nMode == 0)	m_dVectorList[m_nImagePointer].m_nMode = 2;
// 			if (m_dVectorList[m_nImagePointer].m_nMode == 4)	m_dVectorList[m_nImagePointer].m_nMode = 5;
// 		}
// 		if (m_bVectorColor)
// 		{
// 			double	vecscal = Vecmax - Vecmin;
// 			int	nColor;
// 			double	nBias;
// 			for (DWORD i = 0; i<m_dVectorList[m_nImagePointer].m_nVector; i++)
// 			{	//设定向量颜色
// 				if ((m_dVectorList[m_nImagePointer].m_pVector + i)->flag == 0)		(m_dVectorList[m_nImagePointer].m_pVector + i)->m_cVecColor = RGB(0, 0, 0);
// 				else
// 				{
// 					nBias = ((m_dVectorList[m_nImagePointer].m_pVector + i)->fvel - Vecmin);
// 					if (nBias>(vecscal*3.0 / 4.0))		{ nColor = (int)((nBias - vecscal * 3 / 4) * 4 * 255.0 / vecscal);	(m_dVectorList[m_nImagePointer].m_pVector + i)->m_cVecColor = RGB(255, (255 - nColor), 0); }
// 					else if (nBias > (vecscal*2.0 / 4.0))	{ nColor = (int)((nBias - vecscal * 2 / 4) * 4 * 255.0 / vecscal);	(m_dVectorList[m_nImagePointer].m_pVector + i)->m_cVecColor = RGB(nColor, 255, 0); }
// 					else if (nBias > (vecscal / 4.0))		{ nColor = (int)((nBias - vecscal / 4)*4.0*255.0 / vecscal);	(m_dVectorList[m_nImagePointer].m_pVector + i)->m_cVecColor = RGB(0, 255, (255 - nColor)); }
// 					else 	{ nColor = (int)((nBias)*4.0*255.0 / vecscal);		(m_dVectorList[m_nImagePointer].m_pVector + i)->m_cVecColor = RGB(0, nColor, 255); }
// 				}
// 			}
// 		}
// 
// 		lopnumber = 0;
// 		CString sfiledata;
// 		while (strcmp(filedata, "ImageFileName-A:") && strcmp(filedata, "互相关计算图像源文件A:"))	{ lopnumber++;	if (lopnumber > 200)	return false;	fscanf(file, "%s", filedata); }
// 		fscanf(file, "%s", filedata);
// 		sFileName[m_nImagePointer] = filedata;
// 		lopnumber = 0;
// 		while (strcmp(filedata, "ImageFileName-B:") && strcmp(filedata, "互相关计算图像源文件B:"))	{ lopnumber++;	if (lopnumber > 200)	return false;	fscanf(file, "%s", filedata); }
// 		fscanf(file, "%s", filedata);
// 		if ((m_nImagePointer + m_nTwoImage) > m_nImageBuffer)  sFileName[m_nImageBuffer] = filedata;
// 		else sFileName[m_nImagePointer + m_nTwoImage] = filedata;
// 		//[PIV Compute Setting]
// 		lopnumber = 0;
// 		while (strcmp(filedata, "InterrogationWindow:") && strcmp(filedata, "计算参数信息:"))		{ lopnumber++;	if (lopnumber > 200)	return false;	fscanf(file, "%s", filedata); }
// 		fscanf(file, "%s", filedata);
// 		sfiledata = filedata;
// 		sfiledata.Delete(0, 2);
// 		sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 		m_dVectorList[m_nImagePointer].m_pivJobInfo.searchwd = atoi(sfiledata);
// 		fscanf(file, "%s", filedata);
// 		sfiledata = filedata;
// 		sfiledata.Delete(0, 2);
// 		m_dVectorList[m_nImagePointer].m_pivJobInfo.searchht = atoi(sfiledata);
// 		lopnumber = 0;
// 		while (strcmp(filedata, "GridStep:") && strcmp(filedata, "网格步长:"))		{ lopnumber++;	if (lopnumber > 200)	return false;	fscanf(file, "%s", filedata); }
// 		fscanf(file, "%s", filedata);
// 		sfiledata = filedata;
// 		sfiledata.Delete(0, 2);
// 		sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 		m_dVectorList[m_nImagePointer].m_pivJobInfo.stepwd = atoi(sfiledata);
// 		fscanf(file, "%s", filedata);
// 		sfiledata = filedata;
// 		sfiledata.Delete(0, 2);
// 		m_dVectorList[m_nImagePointer].m_pivJobInfo.stepht = atoi(sfiledata);
// 		lopnumber = 0;
// 		while (strcmp(filedata, "StraddleInterval:") && strcmp(filedata, "两幅图像间隔:"))		{ lopnumber++;	if (lopnumber > 200)	return false;	fscanf(file, "%s", filedata); }
// 		fscanf(file, "%s", filedata);
// 		m_nTwoImage = atoi(filedata);		//批处理模式。
// 		if (m_nTwoImage < 0)	m_nTwoImage = 1;
// 		fscanf(file, "%s", filedata);
// 		fscanf(file, "%s", filedata);
// 		sfiledata = filedata;
// 		sfiledata.Delete(0, 2);
// 		sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 		m_dMV_PIV_Setting.m_nShiftX = atoi(sfiledata);
// 		fscanf(file, "%s", filedata);
// 		sfiledata = filedata;
// 		sfiledata.Delete(0, 2);
// 		sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 		m_dMV_PIV_Setting.m_nShiftY = atoi(sfiledata);
// 		if (m_dMV_PIV_Setting.m_nShiftX != 0 || m_dMV_PIV_Setting.m_nShiftY != 0)	m_dMV_PIV_Setting.m_bWithShift = true;
// 		else m_dMV_PIV_Setting.m_bWithShift = false;
// 		fscanf(file, "%s", filedata);
// 		fscanf(file, "%s", filedata);
// 		if (!strcmp(filedata, "True"))	m_dMV_PIV_Setting.m_bWithEqual = true;	//图像预处理选项。
// 		else	m_dMV_PIV_Setting.m_bWithEqual = false;
// 		fscanf(file, "%s", filedata);
// 		fscanf(file, "%s", filedata);
// 		if (!strcmp(filedata, "0"))	{ m_dMV_PIV_Setting.m_bSubMode = false; m_dMV_PIV_Setting.m_nSubModeNumber = 1; }
// 		else { m_dMV_PIV_Setting.m_bSubMode = true;  	m_dMV_PIV_Setting.m_nSubModeNumber = atoi(filedata); }
// 		fscanf(file, "%s", filedata);
// 		fscanf(file, "%s", filedata);
// 		if (!strcmp(filedata, "0"))	m_dMV_PIV_Setting.m_bDistort = false;
// 		else { m_dMV_PIV_Setting.m_bDistort = true;  	m_dMV_PIV_Setting.m_nDistort = atoi(filedata); }
// 		fscanf(file, "%s", filedata);
// 		fscanf(file, "%s", filedata);
// 		if (!strcmp(filedata, "False"))	m_dMV_PIV_Setting.m_bWithFilter = false;
// 		else 	m_dMV_PIV_Setting.m_bWithFilter = true;
// 		fscanf(file, "%s", filedata);
// 		fscanf(file, "%s", filedata);
// 		m_dSerialProcessPIV.m_nInterVal = atoi(filedata);		//批处理模式,图像间隔。
// 		if (m_dSerialProcessPIV.m_nInterVal < 0)		m_dSerialProcessPIV.m_nInterVal = 2;
// 		fscanf(file, "%s", filedata);
// 		if (!strcmp(filedata, "UsingPTVSetting:") && strcmp(filedata, "使用PTV参数:"))		{ fscanf(file, "%s", filedata);		m_dMV_PIV_Setting.m_nPIVADVParticle = atoi(filedata); }
// 		else { fscanf(file, "%s", filedata);		m_dMV_PIV_Setting.m_nPIVADVParticle = atoi(filedata); }
// 		fscanf(file, "%s", filedata);
// 		if (!strcmp(filedata, "VectorCorrectionMode:") || !strcmp(filedata, "向量修正模式:"))
// 		{
// 			fscanf(file, "%s", filedata);		m_pModifyDlg->m_nModifyVector = atoi(filedata);
// 			fscanf(file, "%s", filedata);		fscanf(file, "%s", filedata);	m_dVectorList[m_nImagePointer].m_fModify = atof(filedata);
// 			fscanf(file, "%s", filedata);		fscanf(file, "%s", filedata);	m_pModifyDlg->m_fBias = atof(filedata);
// 			CString	stemp;		stemp.Format("%d", (int)(m_pModifyDlg->m_fBias * 100));
// 			m_pModifyDlg->m_cBias.SetWindowTextA(stemp);
// 			fscanf(file, "%s", filedata);		fscanf(file, "%s", filedata);
// 			m_pModifyDlg->m_fModifyGate = atof(filedata);
// 			if (m_pModifyDlg->m_bModifyDlg)	m_pModifyDlg->UpdateData(false);
// 		}
// 		else	return false;
// 		fscanf(file, "%s", filedata);	//读取背景灰度阈值信息。
// 		fscanf(file, "%s", filedata);
// 		sfiledata = filedata;
// 		m_dMV_PIV_Setting.m_nADGate = atoi(sfiledata);
// 		//	fscanf(file,"%s",filedata);
// 		//	fscanf(file,"%s",filedata);
// 		//	if(!strcmp(filedata,"True"))	m_dSerialProcessPIV.m_nGPUAcc=true;	//GPU加速选项。
// 		lopnumber = 1;
// 		while (strcmp(filedata, "[RulerSetting]") && strcmp(filedata, "标尺窗口参数："))	{ lopnumber++;	if (lopnumber > 200)	break;	fscanf(file, "%s", filedata); }
// 		if (lopnumber<200)
// 		{
// 			lopnumber = 0;
// 			while (strcmp(filedata, "TopLeft:") && strcmp(filedata, "左上："))		{ lopnumber++;	if (lopnumber>200)	return false;	fscanf(file, "%s", filedata); }
// 			fscanf(file, "%s", filedata);
// 			sfiledata = filedata;
// 			sfiledata.Delete(0, 1);
// 			sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 			m_pRulerDlg->m_fPosTLx = (atof(sfiledata));
// 			fscanf(file, "%s", filedata);
// 			sfiledata = filedata;
// 			sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 			m_pRulerDlg->m_fPosTLy = (atof(sfiledata));
// 			lopnumber = 0;
// 			while (strcmp(filedata, "TopRight:") && strcmp(filedata, "右上："))		{ lopnumber++;	if (lopnumber > 200)	return false;	fscanf(file, "%s", filedata); }
// 			fscanf(file, "%s", filedata);
// 			sfiledata = filedata;
// 			sfiledata.Delete(0, 1);
// 			sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 			m_pRulerDlg->m_fPosTRx = (atof(sfiledata));
// 			fscanf(file, "%s", filedata);
// 			sfiledata = filedata;
// 			sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 			m_pRulerDlg->m_fPosTRy = (atof(sfiledata));
// 			lopnumber = 0;
// 			while (strcmp(filedata, "LeftBottom:") && strcmp(filedata, "左下："))		{ lopnumber++;	if (lopnumber > 200)	return false;	fscanf(file, "%s", filedata); }
// 			fscanf(file, "%s", filedata);
// 			sfiledata = filedata;
// 			sfiledata.Delete(0, 1);
// 			sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 			m_pRulerDlg->m_fPosBLx = (atof(sfiledata));
// 			fscanf(file, "%s", filedata);
// 			sfiledata = filedata;
// 			sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 			m_pRulerDlg->m_fPosBLy = (atof(sfiledata));
// 			lopnumber = 0;
// 			while (strcmp(filedata, "RightBottom:") && strcmp(filedata, "右下："))		{ lopnumber++;	if (lopnumber > 200)	return false;	fscanf(file, "%s", filedata); }
// 			fscanf(file, "%s", filedata);
// 			sfiledata = filedata;
// 			sfiledata.Delete(0, 1);
// 			sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 			m_pRulerDlg->m_fPosBRx = (atof(sfiledata));
// 			fscanf(file, "%s", filedata);
// 			sfiledata = filedata;
// 			sfiledata.Delete(sfiledata.GetLength() - 1, 1);
// 			m_pRulerDlg->m_fPosBRy = (atof(sfiledata));
// 			m_pRulerDlg->m_bRulerDlg = true;
// 			if (m_pRulerDlg->GetSafeHwnd() == 0)	m_pRulerDlg->Create();
// 			else	m_pRulerDlg->ShowWindow(SW_SHOW);
// 			m_pRulerDlg->UpdateData(false);
// 		}
// 		else	{ m_pRulerDlg->m_bRulerDlg = false;		m_pRulerDlg->DestroyWindow(); }
// 		lopnumber = 1;	lopstart = fileSize - 500;
// 		if (lopstart<1)	lopstart = 1;
// 		fseek(file, lopstart, SEEK_SET);
// 		while (strcmp(filedata, "[TimeSetting]") && strcmp(filedata, "时间参数："))	{ lopnumber++;	if (lopnumber>500)	break;	fscanf(file, "%s", filedata); }
// 		if (lopnumber < 500)
// 		{
// 			fscanf(file, "%s", filedata);		fscanf(file, "%s", filedata);
// 			(*m_pLaserControl)->m_dFrame = atof(filedata);	m_pRulerDlg->m_fDTime = (*m_pLaserControl)->m_dFrame / 1000.0;				//跨帧时间
// 			fscanf(file, "%s", filedata);		fscanf(file, "%s", filedata);		fscanf(file, "%s", filedata);
// 			(*m_pLaserControl)->m_fCycleTime = atof(filedata);		//工作周期
// 			if (m_pRulerDlg->m_bRulerDlg)	m_pRulerDlg->UpdateData(false);
// 			if ((*m_pLaserControl)->m_bLaserControl)
// 			{
// 				(*m_pLaserControl)->UpdateData(false);
// 				(*m_pLaserControl)->OnLaserSetData();
// 			}
// 		}
// 		fclose(file);
// 		//设定通用计算参数。
// 		m_dMV_PIV_Setting.m_nSearchWD = m_dVectorList[m_nImagePointer].m_pivJobInfo.searchwd;
// 		m_dMV_PIV_Setting.m_nSearchHT = m_dVectorList[m_nImagePointer].m_pivJobInfo.searchht;
// 		m_dMV_PIV_Setting.m_nStepWD = m_dVectorList[m_nImagePointer].m_pivJobInfo.stepwd;
// 		m_dMV_PIV_Setting.m_nStepHT = m_dVectorList[m_nImagePointer].m_pivJobInfo.stepht;
// 		delete m_hVectorBack;
// 	}
// 	m_dVectorList[m_nImagePointer].m_nImageFirst = m_nImagePointer;	m_dVectorList[m_nImagePointer].m_nImageSecond = m_nImagePointer + m_nTwoImage;
// 	m_dVectorList[m_nImagePointer].m_bVector = true;
// 	return true;
// }

