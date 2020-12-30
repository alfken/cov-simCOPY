import React from 'react';
import 'antd/dist/antd.css';
import classes from './MainLayout.module.css';
import { Layout, Menu, Breadcrumb, Card, Space, Button, Switch} from 'antd';
import { UserOutlined, LaptopOutlined, NotificationOutlined } from '@ant-design/icons';
import ForceGraph2D from 'react-force-graph-2d';
import Dashboard from './Dashboard';

// https://medium.com/@jjsincorporated/how-i-built-conways-game-of-life-with-react-hooks-3bc6c2734aa

const { SubMenu } = Menu;
const { Header, Content, Sider } = Layout;
var testData = require('../data/test.json'); //with path
const getStateColor = (n) => {
    switch (n) {
      case 0:
        return '#03c4a1';
      case 1:
        return '#590995';
      case 2:
        return '#c62a88';
      case 3:
        return '#61b15a';
      case 4:
        return '#150485';
      default:
        return '#33b2ff';
    }
  }
  
function genRandomTree(N = 300, reverse = false) {
return {
    nodes: [...Array(N).keys()].map(i => ({ id: i })),
    links: [...Array(N).keys()]
    .filter(id => id)
    .map(id => ({
    [reverse ? 'target' : 'source']: id,
    [reverse ? 'source' : 'target']: Math.round(Math.random() * (id-1)/2)
    }))
};
}

var randomData = genRandomTree(100, false);


function MainLayout() {
    return(
        <Layout>
            <Header className="header" style={{ position: 'fixed', zIndex: 1, width: '100%' }}>
                <h2 style={{
                    marginTop: '8px', 
                    color: 'white', 
                    fontWeight: '250',
                    margin: '8px 10px 10px -25px',
            
                    }}>Covid-19 Simulator</h2>
                <Menu theme="dark" mode="horizontal"
                defaultSelectedKeys={['2']}>
                    <Menu.Item key="1">Home</Menu.Item>
                    <Menu.Item key="2">Simulator</Menu.Item>
                    <Menu.Item key="3">About</Menu.Item>
                </Menu>
                <Switch
                    checkedChildren='+'
                    unCheckedChildren='-'
                    defaultChecked
                    style={{position: 'absolute', right: '12px'}}
                />
            </Header>
            <Layout>
                <Layout style={{ padding: '0 24px 24px'}} >
                        <Breadcrumb style={{ margin: '16px 0', textAlign: "left"}}>
                            <Breadcrumb.Item>Home</Breadcrumb.Item>
                            <Breadcrumb.Item>Graph-based</Breadcrumb.Item>
                            <Breadcrumb.Item>Simulation</Breadcrumb.Item>
                        </Breadcrumb>
                        <Content   
                            className="site-layout-background"
                            style={{
                                padding: 24,
                                margin: 0,
                                minHeight: 280,
                            }}
                        >
                            <Space direction="horizontal">
                                <Card bordered>
                                    <h3>Test Data (with states)</h3>
                                    <ForceGraph2D 
                                        height='500'
                                        width='800'
                                        graphData={testData} 
                                        enableZoomPanInteraction={false}
                                        nodeLabel="state"
                                        nodeCanvasObject={({ state, x, y }, ctx) => {
                                            ctx.fillStyle = getStateColor(state);
                                            ctx.beginPath(); ctx.arc(x, y, 5, 0, 2 * Math.PI, false); ctx.fill(); // circle
                                        }}
                                    />
                                    <Dashboard />     
                                </Card>
                            </Space>                            
                        </Content>
                    </Layout>
                <Sider 
                    width={300} 
                    className="site-layout-background"
                    style={{
                        overflow: 'auto',
                        // overflowY: 'auto',
                        height: '100vh',
                        position: 'fixed',
                        right: 0,
                        // top: "64px",
                        // paddingBottom: "64px",
                        paddingTop: "64px",
                      }}>
                    <Menu
                        mode="inline"
                        defaultSelectedKeys={['1']}
                        defaultOpenKeys={['sub1']}
                        style={{ height: '100%', borderRight: 0}}
                    >
                        <SubMenu key="sub1" icon={<UserOutlined />} title="Simulation setup">
                            <Menu.Item key="1">Timesteps</Menu.Item>
                            <Menu.Item key="2">Initial infections</Menu.Item>
                            <Menu.Item key="3">Graph source type</Menu.Item>
                        </SubMenu>
                        <SubMenu key="sub2" icon={<LaptopOutlined />} title="Groups">
                            <SubMenu key="sub4" title="Base Group Parameters">
                                <Menu.Item key="4">Base Group Parameters</Menu.Item>
                            </SubMenu>
                            <Menu.Item key="5"> <Button block>Add Group</Button></Menu.Item>
                        </SubMenu>
                        <SubMenu key="sub3" icon={<LaptopOutlined />} title="Vaccination settings">
                            
                            <Menu.Item key="6">Vaccination Strategy Type</Menu.Item>
                            <Menu.Item key="7">Vaccination Start Time</Menu.Item>
                            <Menu.Item key="8">Vaccinations available each time step</Menu.Item>
                            <Menu.Item key="8">Vaccinations available each time step</Menu.Item>
                            <Menu.Item key="8">Vaccinations available each time step</Menu.Item>
                            <Menu.Item key="8">Vaccinations available each time step</Menu.Item>


                        </SubMenu>
                        <Space style={{float: 'right', padding: '8px'}}>
                            <Button type="primary">Save</Button>
                            <Button>Reset</Button>        
                        </Space>

                    </Menu>
                </Sider>
            </Layout>
        </Layout>
    )
}

export default MainLayout;