# It Depends software design

This document outlines the design philosofy for _It Depends_' source code.

- [1. Design](#1-class-diagram)
  - [1.1 Interfaces](#11-interfaces)
  - [1.2 Layers](#12-layers)
- [2. Design decisions](#2-design-decisions)

# 1. Design

The code of _It Depends_ is largely made up of three layers, see also [1.2 Layers](#21-layers).

1. Data
2. Domain
3. Presentation

Each of these layers map to a specific namespace in which contracts, implementations and factories are defined. Besides the presentation layer, each layer must only expose data types that are either defined in the standard C++ library or use data types defined in the domain layer of _It Depends_.

To create a specific type from a different layer, a factory must be used to instantiate an implementation, see also [__IDD01__](#21-idd01).

```
TODO: Create class diagram without all implementations
```

## 1.1 Interfaces

All communication in _It Depends_ between two classes should be done through interfaces. This way the implementation is allowed to change.

As a general rule, all interfaces are defined in the `<layer>::contracts` namespace. This gives us the following namespaces where we can define contracts accordingly.

|Namespace|Description|
|:---|:---|
|`domain::contracts`|Here are all contracts stored which are used to execute domain logic, or manipulate models.|
|`data::contracts`|Here are all contracts stored which are responsible for handling different types of data manipultation. Such as reading a file.|

The `presentation` namespace is special in this regard, 'cause the interfaces that are defined in that namespace are very tight to a specific implementation, and no other layer is allowed to communicate with the `presentation` layer. This is a one-way street where the `presentation` layer talks to other layers, but not the other way around.

## 1.2 Layers

_It Depends_ uses the layered pattern, or N-tier pattern, to decouple the different types of partitions most common applications consist of. This pattern groups classes by responsibility and encourages you to place them into the same layer [(Price et Al., 2022)](https://docs.microsoft.com/en-us/azure/architecture/guide/architecture-styles/n-tier).

The following table lists and descibes the different layers that are acknowledged in the code of _It Depends_.

|Layer|Description|
|:----|:----|
|Domain|The domain layer constists of classes exclusive to the domain. This includes classes such as `Dependency`, which represents a dependency that is being displayed to the user. The classes in the domain-layer can only contain classes that are dependent on eachother and should not have any knowledge from another layer.|
|Data|The data layer is used to decouple the domain layer from loading files from the local device. This layer however does have a dependency on the domain layer, because the results of these actions are models.|
|Presentation|The presentation layer is used to display the specific elements from the domain layer, and uses the data layer to retrieve the models which are displayed to the user.|
# 2. Design decisions

Each design decision is numbered with the prefix _IDD_, which stands for _It Depends design Decision_.

## 2.1 IDD01

| __IDD01__        | Communicate between different layers using a factory                                                                                                                    |
|:-----------------|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| __Decision__     | Communicate between different layers using a factory                                                                                                                    |
| __Rationale__    | The method that needs a specific implementation of an interface should not need to know what types are available, and what implementation is best suited for that case. |
| __Alternatives__ | Create an instance of a specific implementation in the method that needs it.                                                                                            |

## 2.2 IDD02

|__IDD02__| Abstract factory design pattern                                                                                                                                                |
|:---|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|__Decision__| Use the abstract factory design pattern to allow the use of multiple factories for each specific use-case                                                                      |
|__Rationale__| A method that needs an implementation of an interface should not be bothered with deciding what type of implementations it might need.                                         |
|__Alternatives__| Use the factory pattern, this isn't chosen because this would require each class to know the exact factory type it should require which goes against [IDD03 - IoC](#23-idd03). |

## 2.3 IDD03

| __IDD03__    |Inversion of Control (IoC)|
|:-------------|:---|
| __Decision__ |Use inversion of control to communicate with dependencies.|
|__Rationale__|This will abstract away the implementation of a dependency which allows the creation of multiple implementations without having to change each user of that dependency.|
|__Alternatives__|Use the direct implementations|

## 2.4 IDD04

|__IDD04__|Constructor injection|
|:----|:----|
|__Decision__|Use constructor injection as a method of using dependency injection|
|__Rationale__|By using constructor injection, all creation of dependencies can be setup in `main.cpp`. This moves the instantiation away from implemenations and moves this to a central (starting) point of the application.|
|__Alternavites__|Using a dependency injection framework. For now, the complexity of setting up and using a DI framework isn't worth the costs. However, in the future this might change.|