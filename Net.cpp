//#include "torch/library.h"
//#include "torch/script.h"
//#include <torch/torch.h>
//
//using namespace torch::nn;
//class MyNet5 : public torch::nn::Module
//{
//public:
//	Conv1d Conv1;
//	MaxPool1d max_pool1;
//	Conv1d Conv2;
//	MaxPool1d max_pool2;
//	Conv1d Conv3;
//	Linear liner1;
//	Linear liner2;
//	Linear liner3;
//
//public:
//	MyNet5() :
//		// (inputchannel, outputchannel, kernel_size)
//		Conv1(Conv1d(Conv2dOptions(1, 10, 3).padding(2).padding_mode(torch::kCircular))),
//		max_pool1(MaxPool1dOptions(3).stride(2)),
//		Conv2(Conv1d(10, 20, 3, 2)),
//		max_pool2(MaxPool1dOptions(3).stride(2)),
//		Conv3(Conv1d(20, 40, 3, 2)),
//
//		liner1(torch::nn::Linear(40 * 14, 120)),
//		liner2(torch::nn::Linear(120, 84)),
//		liner3(torch::nn::Linear(84, 10))
//	{
//		register_module("Conv1", Conv1);
//		register_module("max_pool1", max_pool1);
//		register_module("Conv2", Conv2);
//		register_module("max_pool2", max_pool2);
//		register_module("Conv3", Conv3);
//		register_module("liner1", liner1);
//		register_module("liner3", liner3);
//		register_module("liner3", liner3);
//	}
//
//	torch::Tensor forward(torch::Tensor input)
//	{
//		namespace F = torch::nn::functional;
//
//		auto op_maxpool = F::MaxPool2dFuncOptions(2);
//
//		// forward
//		auto
//		x = F::max_pool2d(F::relu(Conv1(input)), op_maxpool);
//		x = F::max_pool2d(F::relu(Conv2(x)), op_maxpool);
//		x = F::max_pool2d(F::relu(Conv3(x)), op_maxpool);
//		x = x.view({ -1, num_flat_features(x) });
//		x = F::relu(liner1(x));
//		x = F::relu(liner2(x));
//		x = liner3(x);
//
//		return x;
//	}
//
//
//private:
//	long num_flat_features(torch::Tensor x) {
//		// x.size()[1:]  # all dimensions except the batch dimension
//		auto size = x.sizes(); // TODO: Revisit this
//		auto num_features = 1;
//		for (auto s : size) {
//			num_features *= s;
//		}
//		return num_features;
//	}
//};