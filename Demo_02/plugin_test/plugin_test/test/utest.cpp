#include <pluginlib/class_loader.h>
#include <test/test_base.h>
#include <gtest/gtest.h>

TEST(PluginlibTest, unknownPlugin)
{
  pluginlib::ClassLoader<test_base::Fubar> test_loader("pluginlib", "test_base::Fubar");
 // test_base::Fubar* foo = NULL;
 boost::shared_ptr<test_base::Fubar> foo;
  try
  {
    //foo = test_loader.createClassInstance(("pluginlib/foobar"));
    foo = test_loader.createInstance("pluginlib/foobar");
    foo->initialize(10.0);
  }
  catch(pluginlib::LibraryLoadException& ex)
  {
    SUCCEED();
    return;
  }
  catch(...)
  {
    FAIL() << "Uncaught exception";
  }
  ADD_FAILURE() << "Didn't throw exception as expected";
}
TEST(PluginlibTest, createManagedInstanceAndUnloadLibrary)
{
  ROS_INFO( "Making the ClassLoader..." );
  pluginlib::ClassLoader<test_base::Fubar> pl("pluginlib", "test_base::Fubar");

  ROS_INFO( "Instantiating plugin..." );
  {
    boost::shared_ptr<test_base::Fubar> inst = pl.createInstance("pluginlib/foo");
  }

  ROS_INFO( "Checking if plugin is loaded with isClassLoaded..." );
  if( pl.isClassLoaded( "pluginlib/foo" ) )
    ROS_INFO( "Class is loaded" );
  else
  {
    FAIL() <<  "Library containing class should be loaded but isn't.";
  }

  ROS_INFO( "Trying to unload class with unloadLibraryForClass..." );
  try
  {
    pl.unloadLibraryForClass("pluginlib/foo");
  }
  catch(pluginlib::PluginlibException& e)
  {
    FAIL() << "Could not unload library when I should be able to.";
  }
  ROS_INFO( "Done." );
}

// Run all the tests that were declared with TEST()
int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
