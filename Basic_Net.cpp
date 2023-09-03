#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

// Define a Node class to represent individual neurons
class Node {
public:
    Node() : bias(0.0) {}

    // Set the bias for the node
    void setBias(double b) {
        bias = b;
    }

    // Connect this node to another node with a weight
    void addConnection(Node* other, double weight) {
        connections.push_back({ other, weight });
    }

    // Calculate the output of the node
    double calculateOutput() {
        double sum = bias;
        for (const auto& connection : connections) {
            sum += connection.node->output * connection.weight;
        }
        output = sigmoid(sum); // Apply an activation function (e.g., sigmoid)
        return output;
    }

private:
    struct Connection {
        Node* node;
        double weight;
    };

    double bias;
    double output;
    std::vector<Connection> connections;

    // Sigmoid activation function
    double sigmoid(double x) {
        return 1.0 / (1.0 + std::exp(-x));
    }
};

int main() {
    // Create Node objects
    Node inputNode;
    Node hiddenNode1;
    Node hiddenNode2;
    Node outputNode;

    // Connect the nodes with weights
    //connections can be made with the help of combinations
    inputNode.addConnection(&hiddenNode1, 0.5);
    inputNode.addConnection(&hiddenNode2, -0.2);
    hiddenNode1.addConnection(&outputNode, 0.8);
    hiddenNode2.addConnection(&outputNode, 0.6);

    // Set biases for the nodes
  //bias can be trained
    hiddenNode1.setBias(0.3);
    hiddenNode2.setBias(-0.1);
    outputNode.setBias(0.1);

    // Input values
    double inputValue1 = 0.9;
    double inputValue2 = 0.4;

    // Set the input values to the input node
    inputNode.calculateOutput();
    inputNode.output = inputValue1;
    hiddenNode1.calculateOutput();
    hiddenNode2.calculateOutput();

    // Calculate the output of the network
    double networkOutput = outputNode.calculateOutput();

    // Display the result
    std::cout << "Network Output: " << networkOutput << std::endl;

    return 0;
}
