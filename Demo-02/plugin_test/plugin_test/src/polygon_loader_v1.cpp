#include <pluginlib/class_loader.h>
    #include <plugin_test/polygon_base.h>

    #include <ros/ros.h>
    #include <sstream>
    #include <string>
    #include <vector>

    template <typename T>
    std::string to_string(T value) {
        std::ostringstream os ;
        os << value ;
        return os.str() ;
    }

    int main(int argc, char** argv)
    {
      ros::init(argc, argv, "polygon_loader_v1");
      ros::NodeHandle n_;

      std::vector<std::string> class_names;
      int class_index = 1;
      while (true)
      {
        std::string class_name;
        std::string param_name = std::string("polygon_loader_v1/derive_class_" + to_string(class_index++));
        if(!n_.getParam(param_name.c_str(), class_name))
            break;
        class_names.push_back(class_name);
      }

      if (class_names.empty()) {
        ROS_ERROR("ros parameter error");
        return 0;
      }

      pluginlib::ClassLoader<polygon_base::RegularPolygon> poly_loader("plugin_test", "polygon_base::RegularPolygon");

      try
      {

        for (class_index = 0; class_index < class_names.size(); ++class_index) {
          std::string class_name = class_names[class_index];
          boost::shared_ptr<polygon_base::RegularPolygon> plugin = poly_loader.createInstance(class_name);
          plugin->initialize(10.0);
          ROS_INFO("The polygon (%d / %d) area: %.2f", class_index + 1, class_names.size(), plugin->area());
        }
      }
      catch(pluginlib::PluginlibException& ex)
      {
        ROS_ERROR("The plugin failed to load for some reason. Error: %s", ex.what());
      }

      ROS_INFO("Waiting \"Ctrl + C\"");
      while (ros::ok()) {
        ;
      }

      return 0;
    }
